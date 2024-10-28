#!/usr/local/share/pynq-venv/bin/python3
# import libraries

import logging
from modules import logger
from modules.adder import PlAdder
from pynq import PL
from pynq import Overlay


def load_overlay(bit_stream: str) -> PlAdder:

    logging.info("loading overlay from: %s", bit_stream)
    overlay = Overlay(bit_stream)
    print(dir(overlay))
    time_loaded = PL.timestamp
    bit_file = PL.bitfile_name
    gpio = PL.gpio_dict

    logging.info("bitstream %s loaded at %s with gpio %s", bit_file, time_loaded, gpio)
    return overlay


def blinker(overlay: PlAdder) -> None:




if __name__ == "__main__":
    logger.logging_setup(logging_to_file=False, logging_level=logging.INFO)
    ol = load_overlay("/home/py/python/modules/adder/pl_adder.bit")
    blinker(ol)
