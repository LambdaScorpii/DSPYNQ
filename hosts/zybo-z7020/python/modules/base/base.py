#   Copyright (c) 2017, Xilinx, Inc.
#   SPDX-License-Identifier: BSD-3-Clause

import pynq
import pynq.lib


class BaseOverlay(pynq.Overlay):
    """
    The Base overlay for the Zybo-Z7-20

    This overlay is designed to interact with all of the on board peripherals
    and external interfaces of the Pynq-Z1 board. It exposes the following
    attributes:

    Attributes
    ----------
    leds : AxiGPIO
         4-bit output GPIO for interacting with the green LEDs LD0-3
    buttons : AxiGPIO
         4-bit input GPIO for interacting with the buttons BTN0-3
    switches : AxiGPIO
         2-bit input GPIO for interacting with the switches SW0 and SW1
    rgbleds : [pynq.board.RGBLED]
         Wrapper for GPIO for LD4 and LD5 multicolour LEDs
    """

    def __init__(self, bitfile, **kwargs):
        super().__init__(bitfile, **kwargs)
        if self.is_loaded():
            self.leds = self.axi_led.channel1
            self.switches = self.axi_sws.channel1
            self.buttons = self.axi_btn.channel1
            self.leds.setlength(4)
            self.switches.setlength(2)
            self.buttons.setlength(4)
            self.leds.setdirection("out")
            self.switches.setdirection("in")
            self.buttons.setdirection("in")
            self.rgbleds = ([None] * 4) + [pynq.lib.RGBLED(i) for i in range(4, 6)]
