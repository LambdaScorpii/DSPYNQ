from threading import Thread, Event
from queue import Queue
import socket
import logging
import logger
import time


def divide_by(kill_state: Event, data_q: Queue) -> None:
    while not kill_state.is_set():

        try:
            value = 10 / data_q.get()
            logging.info("value is: %s", value)

        except ZeroDivisionError:
            logging.info("Cannot divide by zero")

        except data_q.empty():
            logging.info("No Value given")

        time.sleep(2)


def setup_socket() -> tuple[socket.socket, tuple[int, int]]:
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(("0.0.0.0", 4242))
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server_socket.listen(1)
    logging.info("Server listening on port 4242")

    client_socket, client_address = server_socket.accept()

    # client_socket.makefile()

    logging.debug("socket is: %s", client_socket)

    logging.info(
        "client connected with address: %s:%s", client_address[0], client_address[1]
    )

    return (client_socket, client_address)


def main():
    client_socket = None
    t1 = None
    q = None
    thread_kill = Event()
    thread_kill.clear()
    while True:
        try:
            if not isinstance(client_socket, socket.socket):
                thread_kill.set()
                client_socket = None
                t1 = None
                q = None
                thread_kill.clear()
                client_socket, client_address = setup_socket()
                q = Queue(maxsize=2)
                t1 = Thread(target=divide_by, args=(thread_kill, q), daemon=True)
                t1.start()

            command = client_socket.recv(1)

            if len(command) == 0:
                logging.info("CLient Disconnected, re-establishing connection")
                client_socket.close()
                thread_kill.set()
                t1 = None
                q = None
                client_socket = None

            if isinstance(q, Queue) and not q.full():

                value = int.from_bytes(command, byteorder="big")
                q.put(value)

            else:

                logging.info("Queue is full.")

        except socket.error as e:
            logging.info("Connection error: %s, trying to reconnect", e)
        except KeyboardInterrupt:
            thread_kill.set()
            break


if __name__ == "__main__":
    logger.logging_setup(logging_to_file=False, logging_level=logging.INFO)
    main()
