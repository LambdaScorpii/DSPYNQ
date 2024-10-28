#!/usr/local/share/pynq-venv/bin/python3
# import libraries

import logging
from modules import logger
from modules.base import BaseOverlay
from pynq import PL


def load_overlay(bit_stream: str) -> BaseOverlay:

    logging.info("loading overlay from: %s", bit_stream)
    overlay = BaseOverlay(bit_stream)
    print(dir(overlay))
    time_loaded = PL.timestamp
    bit_file = PL.bitfile_name
    gpio = PL.gpio_dict

    logging.info("bitstream %s loaded at %s with gpio %s", bit_file, time_loaded, gpio)
    return overlay


def blinker(overlay: BaseOverlay) -> None:

    leds = [overlay.leds[i] for i in range(4)]

    rgb_leds = [overlay.rgbleds[i] for i in range(4, 6)]

    while True:
        value = input("Please input value pair for RGB LED: ")

        try:
            rgb_leds[0].on(int(value))

        except Exception as e:
            logging.error("error in value: %s", e)


if __name__ == "__main__":
    logger.logging_setup(logging_to_file=False, logging_level=logging.INFO)
    ol = load_overlay("/home/py/python/modules/base/base.bit")
    blinker(ol)
