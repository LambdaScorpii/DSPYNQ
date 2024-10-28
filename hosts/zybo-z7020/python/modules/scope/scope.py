import logging

from pynq import Overlay
from pynq import PL
from pynq import DefaultHierarchy
from pynq import DefaultIP
from pynq import GPIO


class scope(pynq.Overlay):
    """."""

    def __init__(self, bitfile, **kwargs):
        super().__init__(bitfile, **kwargs)
        if self.is_loaded():
            pass
