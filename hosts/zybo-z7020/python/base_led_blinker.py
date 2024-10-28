#!/usr/local/share/pynq-venv/bin/python3
# import libraries
from time import sleep
from modules import logger
from modules.base import BaseOverlay
from pynq import Overlay
from pynq import PL
import logging


def load_overlay(bit_stream: str) -> BaseOverlay:

    logging.info("loading overlay")
    overlay = BaseOverlay(bit_stream)

    overlay.
    time_loaded = PL.timestamp
    bit_file = PL.bitfile_name
    gpio = PL.gpio_dict

    logging.info("bitstream %s loaded as %s with gpio %s", bit_file, time_loaded, gpio)
    return overlay


def blinker(overlay: Overlay) -> None:

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
    ol = load_overlay("python/modules/base/base.bit")
    blinker(ol)
