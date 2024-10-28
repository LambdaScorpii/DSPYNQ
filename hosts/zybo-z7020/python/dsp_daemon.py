"""Main Function for handling the Camaera Daemon, 
accepting Connection, handles and sending Image Frames"""

# Python Built in Libraries
import socket
import time
import logging
from queue import Queue
import threading


# Pip and APT Libraries
import numpy as np

import pynq


# Own Modules
from modules import logger


def setup_socket(port: int = 4243) -> tuple[socket.socket, tuple[str, int]]:
    """The Function sets up the Socket Server at the given Port.
    Returns the socket object and a Tuple containing the IP Address and
    Port of connectec Client
    """
    server_socket = socket.create_server(
        address=("", port), family=socket.AF_INET6, dualstack_ipv6=True
    )
    # server_socket.listen(1)
    logging.info("Waiting for connection with: %s", server_socket)

    client_socket, client_address = server_socket.accept()

    client_socket.makefile()

    logging.debug("socket is: %s", client_socket)

    logging.info(
        "client connected with address: %s:%s", client_address[0], client_address[1]
    )

    return (client_socket, client_address)


def setup_PL() -> pynq.overlay:
    """Setting up the PL and ADC to be read and defines the Filters."""

    pynq.PL.reset()

    overlay = pynq.Overlay("/home/py/python/modules/scope/scope.bit")

    return overlay


def thread_capture_channel_14(
    suspension_state: threading.Event,
    readings_q: Queue,
    filtered_q: Queue,
    t_q: Queue,
    adc: pynq.mmio,
    kalman_filter: pynq.mmio,
) -> None:
    """ "Thread reading Channel from AD14"""

    mult = 10000

    Q = 1e-4 * mult
    R = 0.1 * mult

    P_k_prev = 1 * mult
    x_k_prev = 0
    while True:
        suspension_state.wait()
        z_k = []
        t = []
        filtered = []
        start = time.perf_counter_ns()
        for _ in range(1500):
            t_elapsed = time.perf_counter_ns() - start

            z_k.append((adc.read(0x200 + (0x10 + 14) * 4) >> 4) / 4096)
            t.append(t_elapsed)

            kalman_filter.write(0x10, int(z_k[_] * mult))
            kalman_filter.write(0x48, int(P_k_prev))
            kalman_filter.write(0x50, int(x_k_prev))
            kalman_filter.write(0x38, int(Q))
            kalman_filter.write(0x40, int(R))

            P_k_prev = kalman_filter.read(0x18)
            x_k_prev = kalman_filter.read(0x28)
            filtered.append(x_k_prev / mult)
        logging.info("Fillinq Queues")
        readings_q.put(np.array(z_k, dtype=np.float32))
        t_q.put(np.array(t, dtype=np.float32))
        filtered_q.put(np.array(filtered, dtype=np.float32))


def thread_capture_channel_15(
    suspension_state: threading.Event,
    readings_q: Queue,
    filtered_q: Queue,
    t_q: Queue,
    adc: pynq.mmio,
    kalman_filter: pynq.mmio,
) -> None:
    """ "Thread reading Channel from AD14"""

    mult = 10000

    Q = 1e-4 * mult
    R = 0.1 * mult

    P_k_prev = 1 * mult
    x_k_prev = 0
    while True:
        suspension_state.wait()
        z_k = []
        t = []
        filtered = []
        start = time.perf_counter_ns()
        for _ in range(1500):
            t_elapsed = time.perf_counter_ns() - start

            z_k.append((adc.read(0x200 + (0x10 + 15) * 4) >> 4) / 4096)
            t.append(t_elapsed)

            kalman_filter.write(0x10, int(z_k[_] * mult))
            kalman_filter.write(0x48, int(P_k_prev))
            kalman_filter.write(0x50, int(x_k_prev))
            kalman_filter.write(0x38, int(Q))
            kalman_filter.write(0x40, int(R))

            P_k_prev = kalman_filter.read(0x18)
            x_k_prev = kalman_filter.read(0x28)
            filtered.append(x_k_prev / mult)
        readings_q.put(np.array(z_k, dtype=np.float32))
        t_q.put(np.array(t, dtype=np.float32))
        filtered_q.put(np.array(filtered, dtype=np.float32))


def thread_capture_channel_6(
    suspension_state: threading.Event,
    readings_q: Queue,
    filtered_q: Queue,
    t_q: Queue,
    adc: pynq.mmio,
    kalman_filter: pynq.mmio,
) -> None:
    """ "Thread reading Channel from AD14"""

    mult = 10000

    Q = 1e-4 * mult
    R = 0.1 * mult

    P_k_prev = 1 * mult
    x_k_prev = 0
    while True:
        suspension_state.wait()
        z_k = []
        t = []
        filtered = []
        start = time.perf_counter_ns()
        for _ in range(1500):
            t_elapsed = time.perf_counter_ns() - start

            z_k.append((adc.read(0x200 + (0x10 + 6) * 4) >> 4) / 4096)
            t.append(t_elapsed)
            kalman_filter.write(0x10, int(z_k[_] * mult))
            kalman_filter.write(0x48, int(P_k_prev))
            kalman_filter.write(0x50, int(x_k_prev))
            kalman_filter.write(0x38, int(Q))
            kalman_filter.write(0x40, int(R))

            P_k_prev = kalman_filter.read(0x18)
            x_k_prev = kalman_filter.read(0x28)
            filtered.append(x_k_prev / mult)
        readings_q.put(np.array(z_k, dtype=np.float32))
        t_q.put(np.array(t, dtype=np.float32))
        filtered_q.put(np.array(filtered, dtype=np.float32))


def thread_capture_channel_7(
    suspension_state: threading.Event,
    readings_q: Queue,
    filtered_q: Queue,
    t_q: Queue,
    adc: pynq.mmio,
    kalman_filter: pynq.mmio,
) -> None:
    """ "Thread reading Channel from AD14"""

    mult = 10000

    Q = 1e-4 * mult
    R = 0.1 * mult

    P_k_prev = 1 * mult
    x_k_prev = 0
    while True:
        suspension_state.wait()
        z_k = []
        t = []
        filtered = []
        start = time.perf_counter_ns()
        for _ in range(1500):
            t_elapsed = time.perf_counter_ns() - start

            z_k.append((adc.read(0x200 + (0x10 + 7) * 4) >> 4) / 4096)
            t.append(t_elapsed)

            kalman_filter.write(0x10, int(z_k[_] * mult))
            kalman_filter.write(0x48, int(P_k_prev))
            kalman_filter.write(0x50, int(x_k_prev))
            kalman_filter.write(0x38, int(Q))
            kalman_filter.write(0x40, int(R))

            P_k_prev = kalman_filter.read(0x18)
            x_k_prev = kalman_filter.read(0x28)
            filtered.append(x_k_prev / mult)
        readings_q.put(np.array(z_k, dtype=np.float32))
        t_q.put(np.array(t, dtype=np.float32))
        filtered_q.put(np.array(filtered, dtype=np.float32))


def main() -> None:
    """The Main Functions creates all worker Threads, Queues and the Socket
    and lets it run. If an error Occures it tries to re-initiate the connection"""

    readings_buffer = 1

    channel_14 = Queue(maxsize=readings_buffer)
    channel_15 = Queue(maxsize=readings_buffer)
    channel_6 = Queue(maxsize=readings_buffer)
    channel_7 = Queue(maxsize=readings_buffer)
    filtered_14 = Queue(maxsize=readings_buffer)
    filtered_15 = Queue(maxsize=readings_buffer)
    filtered_6 = Queue(maxsize=readings_buffer)
    filtered_7 = Queue(maxsize=readings_buffer)
    t_14 = Queue(maxsize=readings_buffer)
    t_15 = Queue(maxsize=readings_buffer)
    t_6 = Queue(maxsize=readings_buffer)
    t_7 = Queue(maxsize=readings_buffer)

    thread_suspension_6 = threading.Event()
    thread_suspension_7 = threading.Event()
    thread_suspension_14 = threading.Event()
    thread_suspension_15 = threading.Event()

    overlay = setup_PL()

    adc = overlay.xadc
    kalman_filter = overlay.kalman_filter

    channel_6_thread = threading.Thread(
        target=thread_capture_channel_6,
        args=(thread_suspension_6, channel_6, filtered_6, t_6, adc, kalman_filter),
        daemon=True,
    )
    channel_6_thread.start()

    channel_7_thread = threading.Thread(
        target=thread_capture_channel_7,
        args=(thread_suspension_7, channel_7, filtered_7, t_7, adc, kalman_filter),
        daemon=True,
    )
    channel_7_thread.start()

    channel_14_thread = threading.Thread(
        target=thread_capture_channel_14,
        args=(thread_suspension_14, channel_14, filtered_14, t_14, adc, kalman_filter),
        daemon=True,
    )
    channel_14_thread.start()

    channel_15_thread = threading.Thread(
        target=thread_capture_channel_15,
        args=(thread_suspension_15, channel_15, filtered_14, t_14, adc, kalman_filter),
        daemon=True,
    )
    channel_15_thread.start()

    thread_suspension_6.set()
    thread_suspension_7.set()
    thread_suspension_14.set()
    thread_suspension_15.set()
    client_socket, client_address = setup_socket()

    while True:
        try:

            command_msg = client_socket.recv(1)

            if len(command_msg) == 0:
                logging.info(
                    "Client disconnected at %s:%s, re-initiating Server",
                    client_address[0],
                    client_address[1],
                )
                client_socket.shutdown(socket.SHUT_RDWR)
                client_socket.close()
                client_socket = None
                client_socket, client_address = setup_socket()

            command = int.from_bytes(command_msg, byteorder="big")
            logging.info(f"command received: { command}")

            match command:

                case 0:
                    logging.info("0 is an illegal command")

                case 6:
                    while True:
                        # ---- Channel 6
                        if channel_6.full():
                            data: np.ndarray = channel_6.get()
                            data = data.tobytes()
                            size = len(data)

                            if size:
                                client_socket.sendall(size.to_bytes(4, byteorder="big"))
                                client_socket.sendall(data)

                            data: np.ndarray = t_6.get()

                            data = data.tobytes()
                            size = len(data)

                            if size:
                                client_socket.sendall(size.to_bytes(4, byteorder="big"))
                                client_socket.sendall(data)

                            data: np.ndarray = filtered_6.get()
                            data = data.tobytes()
                            size = len(data)

                            if size:
                                client_socket.sendall(size.to_bytes(4, byteorder="big"))
                                client_socket.sendall(data)
                                break

                case 7:
                    # ---- Channel 7
                    while True:
                        if channel_7.full():
                            data: np.ndarray = channel_7.get()
                            data = data.tobytes()
                            size = len(data)

                            if size:
                                client_socket.sendall(size.to_bytes(4, byteorder="big"))
                                client_socket.sendall(data)

                            data: np.ndarray = t_7.get()
                            data = data.tobytes()
                            size = len(data)

                            if size:
                                client_socket.sendall(size.to_bytes(4, byteorder="big"))
                                client_socket.sendall(data)

                            data: np.ndarray = filtered_7.get()
                            data = data.tobytes()
                            size = len(data)

                            if size:
                                client_socket.sendall(size.to_bytes(4, byteorder="big"))
                                client_socket.sendall(data)
                                break

                case 14:
                    # ---- Channel 14
                    while True:
                        data = np.array([])
                        if channel_14.full():
                            data: np.ndarray = channel_14.get()

                            data = data.tobytes()
                            size = len(data)

                            if size:

                                client_socket.sendall(size.to_bytes(4, byteorder="big"))
                                client_socket.sendall(data)

                            data: np.ndarray = t_14.get()

                            data = data.tobytes()
                            size = len(data)

                            if size:
                                client_socket.sendall(size.to_bytes(4, byteorder="big"))
                                client_socket.sendall(data)

                            data: np.ndarray = filtered_14.get()
                            data = data.tobytes()
                            size = len(data)

                            if size:
                                client_socket.sendall(size.to_bytes(4, byteorder="big"))
                                client_socket.sendall(data)
                                break

                case 15:
                    # ---- Channel 15
                    while True:
                        data = np.array([])
                        if channel_15.full():
                            data: np.ndarray = channel_15.get()
                            logging.info(data.shape)
                            data = data.tobytes()
                            size = len(data)

                            if size:
                                logging.info("sending: %s", size)
                                client_socket.sendall(size.to_bytes(4, byteorder="big"))
                                client_socket.sendall(data)

                            data: np.ndarray = t_15.get()
                            logging.info(data.shape)
                            data = data.tobytes()
                            size = len(data)

                            if size:
                                client_socket.sendall(size.to_bytes(4, byteorder="big"))
                                client_socket.sendall(data)

                            data: np.ndarray = filtered_15.get()
                            data = data.tobytes()
                            size = len(data)

                            if size:
                                client_socket.sendall(size.to_bytes(4, byteorder="big"))
                                client_socket.sendall(data)
                                break

        except socket.error as e:
            logging.info("Connection error: %s, trying to restart socket", e)
            client_socket, client_address = setup_socket()

        except KeyboardInterrupt:
            break


if __name__ == "__main__":
    logger.logging_setup(logging_to_file=False, logging_level=logging.INFO)
    main()
