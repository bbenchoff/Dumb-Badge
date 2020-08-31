#!/usr/bin/env python3
"""Generate a set of EAGLE footprints for keyboard switches.

This script generates a complete set of Cherry MX switch footprints for various
switch configurations and uses. I wrote it to make generating and changing my
switch footprints manageable.
"""
from collections import OrderedDict
from copy import copy
from decimal import Decimal
from jinja2 import Template


switch_pins = [
    {'name': 'P0', 'x': '-10.16', 'y': '2.54', 'visible': 'both', 'length': 'short', 'swaplevel': '1'},
    {'name': 'P1', 'x': '2.54', 'y': '10.16', 'visible': 'both', 'length': 'short', 'rot': 'R270', 'swaplevel': '1'}
]
switch_led_plus = [
    {'name': 'LED+', 'x': '10.16', 'y': '0', 'visible': 'both', 'length': 'short', 'rot': 'R180'}
]
switch_led_minus = [
    {'name': 'LED-', 'x': '-2.54', 'y': '-10.16', 'visible': 'both', 'length': 'short', 'rot': 'R90'}
]
switch_led_rgb = [
    {'name': 'R-', 'x': '-5.08', 'y': '-10.16', 'visible': 'both', 'length': 'short', 'rot': 'R90'},
    {'name': 'G-', 'x': '-2.54', 'y': '-10.16', 'visible': 'both', 'length': 'short', 'rot': 'R90'},
    {'name': 'B-', 'x': '0', 'y': '-10.16', 'visible': 'both', 'length': 'short', 'rot': 'R90'}
]
switch_diode = [
    {'name': 'D+', 'x': '10.16', 'y': '0', 'visible': 'both', 'length': 'short', 'rot': 'R180'},
    {'name': 'D-', 'x': '-5.08', 'y': '-10.16', 'visible': 'both', 'length': 'short', 'rot': 'R90'}
]
switch_symbol_labels = [
    {'value': '&gt;NAME', 'x': '-6.81', 'y': '5.318', 'size': '1', 'layer': '95'}
]
switch_symbol_outline = [
    {'x1': '-7.54', 'y1': '7.54', 'x2': '7.54', 'y2': '7.54', 'width': '0.254', 'layer': '94'},
    {'x1': '7.54', 'y1': '7.54', 'x2': '7.54', 'y2': '-7.54', 'width': '0.254', 'layer': '94'},
    {'x1': '7.54', 'y1': '-7.54', 'x2': '-7.54', 'y2': '-7.54', 'width': '0.254', 'layer': '94'},
    {'x1': '-7.54', 'y1': '-7.54', 'x2': '-7.54', 'y2': '7.54', 'width': '0.254', 'layer': '94'},
]
switch_sizes = {
    '1': {},
    '2': {'lstab': -11.9, 'rstab': 11.9, 'tstab': 7, 'bstab': -8.24},
    '4': {'lstab': -28.625, 'rstab': 28.625, 'tstab': 7, 'bstab': -8.24},
    '6': {'lstab': -57.15, 'rstab': 38.1, 'tstab': 7, 'bstab': -8.24},
    '-6': {'lstab': -38.1, 'rstab': 57.15, 'tstab': 7, 'bstab': -8.24},
    '6.25': {'lstab': -50, 'rstab': 50, 'tstab': 7, 'bstab': -8.24},
    '6.5': {'lstab': -52.5, 'rstab': 52.5, 'tstab': 7, 'bstab': -8.24},
    '7': {'lstab': -57.15, 'rstab': 57.15, 'tstab': 7, 'bstab': -8.24}
}
connects = {
    'ALPS': [
        {'gate': 'G$1', 'pin': 'P0', 'pad': 'ALPS1'},
        {'gate': 'G$1', 'pin': 'P1', 'pad': 'ALPS2'}
    ],
    'ALPSPLATE': [
    ],
    'ALPSMX': [
        {'gate': 'G$1', 'pin': 'P0', 'pad': 'ALPS1 MX1'},
        {'gate': 'G$1', 'pin': 'P1', 'pad': 'ALPS2 MX2'}
    ],
    'ALPSMXPLATE': [
    ],
    'ALPSMXMIR': [
        {'gate': 'G$1', 'pin': 'P0', 'pad': 'ALPS1 ALPS3 MX1 MX3'},
        {'gate': 'G$1', 'pin': 'P1', 'pad': 'ALPS2 ALPS4 MX2 MX4'}
    ],
    'CHOC': [
        {'gate': 'G$1', 'pin': 'P0', 'pad': 'CHOC1'},
        {'gate': 'G$1', 'pin': 'P1', 'pad': 'CHOC2'}
    ],
    'CHOCX': [
        {'gate': 'G$1', 'pin': 'P0', 'pad': 'CHOC1 X1'},
        {'gate': 'G$1', 'pin': 'P1', 'pad': 'CHOC2 X2'}
    ],
    'MX': [
        {'gate': 'G$1', 'pin': 'P0', 'pad': 'MX1'},
        {'gate': 'G$1', 'pin': 'P1', 'pad': 'MX2'}
    ],
    'MXPLATE': [
    ],
    'MXHS': [
        {'gate': 'G$1', 'pin': 'P0', 'pad': 'MX1'},
        {'gate': 'G$1', 'pin': 'P1', 'pad': 'MX2'}
    ],
    'MXHSPCB': [
        {'gate': 'G$1', 'pin': 'P0', 'pad': 'MX1'},
        {'gate': 'G$1', 'pin': 'P1', 'pad': 'MX2'}
    ],
    'X': [
        {'gate': 'G$1', 'pin': 'P0', 'pad': 'X1'},
        {'gate': 'G$1', 'pin': 'P1', 'pad': 'X2'}
    ],
}
package_holes = {
    'ALPS': [],
    'ALPSPLATE': [],
    'ALPSMX': [
        {'x': '0', 'y': '0', 'diameter': '4'},
        {'x': '-5.08', 'y': '0', 'diameter': '1.7'},
        {'x': '5.08', 'y': '0', 'diameter': '1.7'},
    ],
    'ALPSMXMIR': [
        {'x': '0', 'y': '0', 'diameter': '4'},
        {'x': '-5.08', 'y': '0', 'diameter': '1.7'},
        {'x': '5.08', 'y': '0', 'diameter': '1.7'},
    ],
    'ALPSMXPLATE': [],
    'CHOC': [
        {'x': '0', 'y': '0', 'diameter': '3.4'},
        {'x': '-5.22', 'y': '-4.2', 'diameter': '0.6'},
        {'x': '-5.5', 'y': '0', 'diameter': '1.85'},
        {'x': '5.5', 'y': '0', 'diameter': '1.85'}
    ],
    'CHOCX': [
        {'x': '-5.22', 'y': '-4.2', 'diameter': '0.6'},
        {'x': '-5.5', 'y': '5.5', 'diameter': '1.3'},
        {'x': '5.5', 'y': '-5.5', 'diameter': '1.3'},
        {'x': '-5.5', 'y': '0', 'diameter': '1.85'},
        {'x': '5.5', 'y': '0', 'diameter': '1.85'}
    ],
    'MX': [
        {'x': '0', 'y': '0', 'diameter': '4'},
        {'x': '-5.08', 'y': '0', 'diameter': '1.7'},
        {'x': '5.08', 'y': '0', 'diameter': '1.7'},
    ],
    'MXHS': [
        {'x': '0', 'y': '0', 'diameter': '4'},
        {'x': '3.81', 'y': '2.54', 'diameter': '3'},
        {'x': '-2.54', 'y': '5.08', 'diameter': '3'},
    ],
    'MXHSPCB': [
        {'x': '0', 'y': '0', 'diameter': '4'},
        {'x': '5.08', 'y': '0', 'diameter': '1.7'},
        {'x': '-5.08', 'y': '0', 'diameter': '1.7'},
        {'x': '3.81', 'y': '2.54', 'diameter': '3'},
        {'x': '-2.54', 'y': '5.08', 'diameter': '3'},
    ],
    'MXPLATE': [],
    'X': [
        {'x': '-5.5', 'y': '0', 'diameter': '1.85'},
        {'x': '5.5', 'y': '0', 'diameter': '1.85'}
    ],
}
package_pads = {
    'ALPS': [
        {'name': 'ALPS1', 'x': '-2.5', 'y': '4', 'drill': '1.3', 'diameter': '2.54'},
        {'name': 'ALPS2', 'x': '2.5', 'y': '4.5', 'drill': '1.3', 'diameter': '2.54'}
    ],
    'ALPSPLATE': [
    ],
    'ALPSMX': [
        {'name': 'MX1', 'x': '-3.81', 'y': '2.54', 'drill': '1.3', 'diameter': '2.54'},
        {'name': 'MX2', 'x': '2.54', 'y': '5.08', 'drill': '1.3', 'diameter': '2.54'},
        {'name': 'ALPS1', 'x': '-2.5', 'y': '4', 'drill': '1.3', 'diameter': '2.54'},
        {'name': 'ALPS2', 'x': '2.5', 'y': '4.5', 'drill': '1.3', 'diameter': '2.54'}
    ],
    'ALPSMXMIR': [
        {'name': 'MX1', 'x': '-3.81', 'y': '2.54', 'drill': '1.3', 'diameter': '2.54'},
        {'name': 'MX2', 'x': '2.54', 'y': '5.08', 'drill': '1.3', 'diameter': '2.54'},
        {'name': 'MX3', 'x': '-2.54', 'y': '5.08', 'drill': '1.3', 'diameter': '2.54'},
        {'name': 'MX4', 'x': '3.81', 'y': '2.54', 'drill': '1.3', 'diameter': '2.54'},
        {'name': 'ALPS1', 'x': '-2.5', 'y': '4', 'drill': '1.3', 'diameter': '2.54'},
        {'name': 'ALPS2', 'x': '2.5', 'y': '4.5', 'drill': '1.3', 'diameter': '2.54'},
        {'name': 'ALPS3', 'x': '-2.5', 'y': '4.5', 'drill': '1.3', 'diameter': '2.54'},
        {'name': 'ALPS4', 'x': '2.5', 'y': '4', 'drill': '1.3', 'diameter': '2.54'}
    ],
    'ALPSMXPLATE': [
    ],
    'CHOC': [
        {'name': 'CHOC1', 'x': '0', 'y': '5.9', 'drill': '1.2', 'diameter': '2.54'},
        {'name': 'CHOC2', 'x': '5', 'y': '3.8', 'drill': '1.2', 'diameter': '2.54'}
    ],
    'CHOCX': [
        {'name': 'CHOC1', 'x': '0', 'y': '5.9', 'drill': '1.2', 'diameter': '2.54'},
        {'name': 'CHOC2', 'x': '5', 'y': '3.8', 'drill': '1.2', 'diameter': '2.54'},
        {'name': 'X1', 'x': '-3.4', 'y': '2.9', 'drill': '1.3', 'diameter': '2.54'},
        {'name': 'X2', 'x': '-3.4', 'y': '-2', 'drill': '1.3', 'diameter': '2.54'}
    ],
    'MX': [
        {'name': 'MX1', 'x': '-3.81', 'y': '2.54', 'drill': '1.3', 'diameter': '2.54'},
        {'name': 'MX2', 'x': '2.54', 'y': '5.08', 'drill': '1.3', 'diameter': '2.54'}
    ],
    'MXPLATE': [
    ],
    'MXHS': [],
    'MXHSPCB': [],
    'X': [
        {'name': 'X1', 'x': '-3.4', 'y': '2.9', 'drill': '1.3', 'diameter': '2.54'},
        {'name': 'X2', 'x': '-3.4', 'y': '-2', 'drill': '1.3', 'diameter': '2.54'}
    ],
}
package_smds = {
    'ALPS': [],
    'ALPSPLATE': [],
    'ALPSMX': [],
    'ALPSMXMIR': [],
    'ALPSMXPLATE': [],
    'CHOC': [],
    'CHOCX': [],
    'MX': [],
    'MXPLATE': [],
    'MXHS': [
        {'name': 'MX1', 'x': '7.36', 'y': '2.54', 'dx': '2.55', 'dy': '2.5', 'layer': '1'},
        {'name': 'MX2', 'x': '-6.09', 'y': '5.08', 'dx': '2.55', 'dy': '2.5', 'layer': '1'}
    ],
    'MXHSPCB': [
        {'name': 'MX1', 'x': '7.36', 'y': '2.54', 'dx': '2.55', 'dy': '2.5', 'layer': '1'},
        {'name': 'MX2', 'x': '-6.09', 'y': '5.08', 'dx': '2.55', 'dy': '2.5', 'layer': '1'}
    ],
    'X': []
}
package_wires = {
    'ALPS': [
        {'x1': '7.75', 'y1': '7', 'x2': '7.75', 'y2': '-7', 'width': '0.125', 'layer': '47'},
        {'x1': '7.75', 'y1': '-7', 'x2': '-7.75', 'y2': '-7', 'width': '0.125', 'layer': '47'},
        {'x1': '-7.75', 'y1': '-7', 'x2': '-7.75', 'y2': '7', 'width': '0.125', 'layer': '47'},
        {'x1': '-7.75', 'y1': '7', 'x2': '7.75', 'y2': '7', 'width': '0.125', 'layer': '47'},
    ],
    'ALPSPLATE': [
        {'x1': '7.75', 'y1': '7', 'x2': '7.75', 'y2': '-7', 'width': '0', 'layer': '20'},
        {'x1': '7.75', 'y1': '-7', 'x2': '-7.75', 'y2': '-7', 'width': '0', 'layer': '20'},
        {'x1': '-7.75', 'y1': '-7', 'x2': '-7.75', 'y2': '7', 'width': '0', 'layer': '20'},
        {'x1': '-7.75', 'y1': '7', 'x2': '7.75', 'y2': '7', 'width': '0', 'layer': '20'},
    ],
    'ALPSMX': [
        {'x1': '-7', 'y1': '8', 'x2': '7', 'y2': '8', 'width': '0.125', 'layer': '47'},
        {'x1': '7.75', 'y1': '7', 'x2': '7.75', 'y2': '-7', 'width': '0.125', 'layer': '47'},
        {'x1': '7', 'y1': '-8', 'x2': '-7', 'y2': '-8', 'width': '0.125', 'layer': '47'},
        {'x1': '-7.75', 'y1': '-7', 'x2': '-7.75', 'y2': '7', 'width': '0.125', 'layer': '47'},
        {'x1': '-7.75', 'y1': '7', 'x2': '-7', 'y2': '7', 'width': '0.125', 'layer': '47'},
        {'x1': '-7', 'y1': '7', 'x2': '-7', 'y2': '8', 'width': '0.125', 'layer': '47'},
        {'x1': '7', 'y1': '8', 'x2': '7', 'y2': '7', 'width': '0.125', 'layer': '47'},
        {'x1': '7', 'y1': '7', 'x2': '7.75', 'y2': '7', 'width': '0.125', 'layer': '47'},
        {'x1': '7.75', 'y1': '-7', 'x2': '7', 'y2': '-7', 'width': '0.125', 'layer': '47'},
        {'x1': '7', 'y1': '-7', 'x2': '7', 'y2': '-8', 'width': '0.125', 'layer': '47'},
        {'x1': '-7', 'y1': '-8', 'x2': '-7', 'y2': '-7', 'width': '0.125', 'layer': '47'},
        {'x1': '-7', 'y1': '-7', 'x2': '-7.75', 'y2': '-7', 'width': '0.125', 'layer': '47'}
    ],
    'ALPSMXMIR': [
        {'x1': '-7', 'y1': '8', 'x2': '7', 'y2': '8', 'width': '0.125', 'layer': '47'},
        {'x1': '7.75', 'y1': '7', 'x2': '7.75', 'y2': '-7', 'width': '0.125', 'layer': '47'},
        {'x1': '7', 'y1': '-8', 'x2': '-7', 'y2': '-8', 'width': '0.125', 'layer': '47'},
        {'x1': '-7.75', 'y1': '-7', 'x2': '-7.75', 'y2': '7', 'width': '0.125', 'layer': '47'},
        {'x1': '-7.75', 'y1': '7', 'x2': '-7', 'y2': '7', 'width': '0.125', 'layer': '47'},
        {'x1': '-7', 'y1': '7', 'x2': '-7', 'y2': '8', 'width': '0.125', 'layer': '47'},
        {'x1': '7', 'y1': '8', 'x2': '7', 'y2': '7', 'width': '0.125', 'layer': '47'},
        {'x1': '7', 'y1': '7', 'x2': '7.75', 'y2': '7', 'width': '0.125', 'layer': '47'},
        {'x1': '7.75', 'y1': '-7', 'x2': '7', 'y2': '-7', 'width': '0.125', 'layer': '47'},
        {'x1': '7', 'y1': '-7', 'x2': '7', 'y2': '-8', 'width': '0.125', 'layer': '47'},
        {'x1': '-7', 'y1': '-8', 'x2': '-7', 'y2': '-7', 'width': '0.125', 'layer': '47'},
        {'x1': '-7', 'y1': '-7', 'x2': '-7.75', 'y2': '-7', 'width': '0.125', 'layer': '47'}
    ],
    'ALPSMXPLATE': [
        {'x1': '-7', 'y1': '8', 'x2': '7', 'y2': '8', 'width': '0', 'layer': '20'},
        {'x1': '7.75', 'y1': '7', 'x2': '7.75', 'y2': '-7', 'width': '0', 'layer': '20'},
        {'x1': '7', 'y1': '-8', 'x2': '-7', 'y2': '-8', 'width': '0', 'layer': '20'},
        {'x1': '-7.75', 'y1': '-7', 'x2': '-7.75', 'y2': '7', 'width': '0', 'layer': '20'},
        {'x1': '-7.75', 'y1': '7', 'x2': '-7', 'y2': '7', 'width': '0', 'layer': '20'},
        {'x1': '-7', 'y1': '7', 'x2': '-7', 'y2': '8', 'width': '0', 'layer': '20'},
        {'x1': '7', 'y1': '8', 'x2': '7', 'y2': '7', 'width': '0', 'layer': '20'},
        {'x1': '7', 'y1': '7', 'x2': '7.75', 'y2': '7', 'width': '0', 'layer': '20'},
        {'x1': '7.75', 'y1': '-7', 'x2': '7', 'y2': '-7', 'width': '0', 'layer': '20'},
        {'x1': '7', 'y1': '-7', 'x2': '7', 'y2': '-8', 'width': '0', 'layer': '20'},
        {'x1': '-7', 'y1': '-8', 'x2': '-7', 'y2': '-7', 'width': '0', 'layer': '20'},
        {'x1': '-7', 'y1': '-7', 'x2': '-7.75', 'y2': '-7', 'width': '0', 'layer': '20'}
    ],
    'CHOC': [
        {'x1': "-7", 'y1': "7", 'x2': "7", 'y2': "7", 'width': "0.125", 'layer': "47"},
        {'x1': "7", 'y1': "7", 'x2': "7", 'y2': "-7", 'width': "0.125", 'layer': "47"},
        {'x1': "7", 'y1': "-7", 'x2': "-7", 'y2': "-7", 'width': "0.125", 'layer': "47"},
        {'x1': "-7", 'y1': "-7", 'x2': "-7", 'y2': "7", 'width': "0.125", 'layer': "47"},
        {'x1': "-1.7", 'y1': "-4.05", 'x2': "1.7", 'y2': "-4.05", 'width': "0.1", 'layer': "47"},
        {'x1': "1.7", 'y1': "-4.05", 'x2': "1.7", 'y2': "-5.55", 'width': "0.1", 'layer': "47"},
        {'x1': "1.7", 'y1': "-5.55", 'x2': "-1.7", 'y2': "-5.55", 'width': "0.1", 'layer': "47"},
        {'x1': "-1.7", 'y1': "-5.55", 'x2': "-1.7", 'y2': "-4.05", 'width': "0.1", 'layer': "47"}
    ],
    'CHOCX': [
        {'x1': "-7", 'y1': "7", 'x2': "7", 'y2': "7", 'width': "0.125", 'layer': "47"},
        {'x1': "7", 'y1': "7", 'x2': "7", 'y2': "-7", 'width': "0.125", 'layer': "47"},
        {'x1': "7", 'y1': "-7", 'x2': "-7", 'y2': "-7", 'width': "0.125", 'layer': "47"},
        {'x1': "-7", 'y1': "-7", 'x2': "-7", 'y2': "7", 'width': "0.125", 'layer': "47"},
        {'x1': "-1.7", 'y1': "-4.05", 'x2': "1.7", 'y2': "-4.05", 'width': "0.1", 'layer': "47"},
        {'x1': "1.7", 'y1': "-4.05", 'x2': "1.7", 'y2': "-5.55", 'width': "0.1", 'layer': "47"},
        {'x1': "1.7", 'y1': "-5.55", 'x2': "-1.7", 'y2': "-5.55", 'width': "0.1", 'layer': "47"},
        {'x1': "-1.7", 'y1': "-5.55", 'x2': "-1.7", 'y2': "-4.05", 'width': "0.1", 'layer': "47"},
        {'x1': "2.3", 'y1': "-2.95", 'x2': "-2.3", 'y2': "-2.95", 'width': "0", 'layer': "20"},
        {'x1': "-2.3", 'y1': "-2.95", 'x2': "-2.55", 'y2': "-2.7", 'width': "0", 'layer': "20", 'curve': "-90"},
        {'x1': "-2.55", 'y1': "-2.7", 'x2': "-2.55", 'y2': "0.9", 'width': "0", 'layer': "20"},
        {'x1': "-2.55", 'y1': "0.9", 'x2': "-2.3", 'y2': "1.15", 'width': "0", 'layer': "20", 'curve': "-90"},
        {'x1': "-2.3", 'y1': "1.15", 'x2': "-1.39", 'y2': "1.15", 'width': "0", 'layer': "20"},
        {'x1': "1.39", 'y1': "1.15", 'x2': "2.3", 'y2': "1.15", 'width': "0", 'layer': "20"},
        {'x1': "2.3", 'y1': "1.15", 'x2': "2.55", 'y2': "0.9", 'width': "0", 'layer': "20", 'curve': "-90"},
        {'x1': "2.55", 'y1': "0.9", 'x2': "2.55", 'y2': "-2.7", 'width': "0", 'layer': "20"},
        {'x1': "2.55", 'y1': "-2.7", 'x2': "2.3", 'y2': "-2.95", 'width': "0", 'layer': "20", 'curve': "-90"},
        {'x1': "-1.39", 'y1': "1.15", 'x2': "1.39", 'y2': "1.15", 'width': "0", 'layer': "20", 'curve': "-100.795498"}
    ],
    'MX': [
        {'x1': '-7', 'y1': '7', 'x2': '7', 'y2': '7', 'width': '0.125', 'layer': '47'},
        {'x1': '7', 'y1': '7', 'x2': '7', 'y2': '-7', 'width': '0.125', 'layer': '47'},
        {'x1': '7', 'y1': '-7', 'x2': '-7', 'y2': '-7', 'width': '0.125', 'layer': '47'},
        {'x1': '-7', 'y1': '-7', 'x2': '-7', 'y2': '7', 'width': '0.125', 'layer': '47'},
    ],
    'MXHS': [
        {'x1': '-7', 'y1': '7', 'x2': '7', 'y2': '7', 'width': '0.15', 'layer': '47'},
        {'x1': '7', 'y1': '7', 'x2': '7', 'y2': '-7', 'width': '0.15', 'layer': '47'},
        {'x1': '7', 'y1': '-7', 'x2': '-7', 'y2': '-7', 'width': '0.15', 'layer': '47'},
        {'x1': '-7', 'y1': '-7', 'x2': '-7', 'y2': '7', 'width': '0.15', 'layer': '47'},
        {'x1': '5.5', 'y1': '0.8', 'x2': '5.5', 'y2': '4.6', 'width': '0.15', 'layer': '21'},
        {'x1': '5.5', 'y1': '4.6', 'x2': '3.3', 'y2': '6.8', 'width': '0.15', 'layer': '21', 'curve': '90'},
        {'x1': '3.3', 'y1': '6.8', 'x2': '-4.3', 'y2': '6.8', 'width': '0.15', 'layer': '21'},
        {'x1': '-4.3', 'y1': '6.8', 'x2': '-4.3', 'y2': '3.85', 'width': '0.15', 'layer': '21'},
        {'x1': '-4.3', 'y1': '3.85', 'x2': '-3.7', 'y2': '3.3', 'width': '0.15', 'layer': '21', 'curve': '90'},
        {'x1': '-3.7', 'y1': '3.3', 'x2': '0.3', 'y2': '3.3', 'width': '0.15', 'layer': '21'},
        {'x1': '0.3', 'y1': '3.3', 'x2': '2.3', 'y2': '1.5', 'width': '0.15', 'layer': '21', 'curve': '-90'},
        {'x1': '2.3', 'y1': '1.5', 'x2': '2.3', 'y2': '1.35', 'width': '0.15', 'layer': '21'},
        {'x1': '2.3', 'y1': '1.35', 'x2': '2.65', 'y2': '0.8', 'width': '0.15', 'layer': '21', 'curve': '90'},
        {'x1': '2.65', 'y1': '0.8', 'x2': '5.5', 'y2': '0.8', 'width': '0.15', 'layer': '21'},
    ],
    'MXHSPCB': [
        {'x1': '-7', 'y1': '7', 'x2': '7', 'y2': '7', 'width': '0.15', 'layer': '47'},
        {'x1': '7', 'y1': '7', 'x2': '7', 'y2': '-7', 'width': '0.15', 'layer': '47'},
        {'x1': '7', 'y1': '-7', 'x2': '-7', 'y2': '-7', 'width': '0.15', 'layer': '47'},
        {'x1': '-7', 'y1': '-7', 'x2': '-7', 'y2': '7', 'width': '0.15', 'layer': '47'},
        {'x1': '5.5', 'y1': '0.8', 'x2': '5.5', 'y2': '4.6', 'width': '0.15', 'layer': '21'},
        {'x1': '5.5', 'y1': '4.6', 'x2': '3.3', 'y2': '6.8', 'width': '0.15', 'layer': '21', 'curve': '90'},
        {'x1': '3.3', 'y1': '6.8', 'x2': '-4.3', 'y2': '6.8', 'width': '0.15', 'layer': '21'},
        {'x1': '-4.3', 'y1': '6.8', 'x2': '-4.3', 'y2': '3.85', 'width': '0.15', 'layer': '21'},
        {'x1': '-4.3', 'y1': '3.85', 'x2': '-3.7', 'y2': '3.3', 'width': '0.15', 'layer': '21', 'curve': '90'},
        {'x1': '-3.7', 'y1': '3.3', 'x2': '0.3', 'y2': '3.3', 'width': '0.15', 'layer': '21'},
        {'x1': '0.3', 'y1': '3.3', 'x2': '2.3', 'y2': '1.5', 'width': '0.15', 'layer': '21', 'curve': '-90'},
        {'x1': '2.3', 'y1': '1.5', 'x2': '2.3', 'y2': '1.35', 'width': '0.15', 'layer': '21'},
        {'x1': '2.3', 'y1': '1.35', 'x2': '2.65', 'y2': '0.8', 'width': '0.15', 'layer': '21', 'curve': '90'},
        {'x1': '2.65', 'y1': '0.8', 'x2': '5.5', 'y2': '0.8', 'width': '0.15', 'layer': '21'},
    ],
    'MXPLATE': [
        {'x1': '-7', 'y1': '7', 'x2': '7', 'y2': '7', 'width': '0', 'layer': '20'},
        {'x1': '7', 'y1': '7', 'x2': '7', 'y2': '-7', 'width': '0', 'layer': '20'},
        {'x1': '7', 'y1': '-7', 'x2': '-7', 'y2': '-7', 'width': '0', 'layer': '20'},
        {'x1': '-7', 'y1': '-7', 'x2': '-7', 'y2': '7', 'width': '0', 'layer': '20'},
    ],
    'X': [
        {'x1': "-7", 'y1': "7", 'x2': "7", 'y2': "7", 'width': "0.125", 'layer': "47"},
        {'x1': "7", 'y1': "7", 'x2': "7", 'y2': "-7", 'width': "0.125", 'layer': "47"},
        {'x1': "7", 'y1': "-7", 'x2': "-7", 'y2': "-7", 'width': "0.125", 'layer': "47"},
        {'x1': "-7", 'y1': "-7", 'x2': "-7", 'y2': "7", 'width': "0.125", 'layer': "47"},
        {'x1': "-1.7", 'y1': "-4.05", 'x2': "1.7", 'y2': "-4.05", 'width': "0.1", 'layer': "47"},
        {'x1': "1.7", 'y1': "-4.05", 'x2': "1.7", 'y2': "-5.55", 'width': "0.1", 'layer': "47"},
        {'x1': "1.7", 'y1': "-5.55", 'x2': "-1.7", 'y2': "-5.55", 'width': "0.1", 'layer': "47"},
        {'x1': "-1.7", 'y1': "-5.55", 'x2': "-1.7", 'y2': "-4.05", 'width': "0.1", 'layer': "47"},
        {'x1': "2.3", 'y1': "-2.95", 'x2': "-2.3", 'y2': "-2.95", 'width': "0", 'layer': "20"},
        {'x1': "-2.3", 'y1': "-2.95", 'x2': "-2.55", 'y2': "-2.7", 'width': "0", 'layer': "20", 'curve': "-90"},
        {'x1': "-2.55", 'y1': "-2.7", 'x2': "-2.55", 'y2': "0.9", 'width': "0", 'layer': "20"},
        {'x1': "-2.55", 'y1': "0.9", 'x2': "-2.3", 'y2': "1.15", 'width': "0", 'layer': "20", 'curve': "-90"},
        {'x1': "-2.3", 'y1': "1.15", 'x2': "2.3", 'y2': "1.15", 'width': "0", 'layer': "20"},
        {'x1': "2.3", 'y1': "1.15", 'x2': "2.55", 'y2': "0.9", 'width': "0", 'layer': "20", 'curve': "-90"},
        {'x1': "2.55", 'y1': "0.9", 'x2': "2.55", 'y2': "-2.7", 'width': "0", 'layer': "20"},
        {'x1': "2.55", 'y1': "-2.7", 'x2': "2.3", 'y2': "-2.95", 'width': "0", 'layer': "20", 'curve': "-90"},
    ]
}
devices = {
    'PLAIN': {
        'switch_types': ['ALPS', 'ALPSMX', 'ALPSMXMIR', 'CHOC', 'CHOCX', 'MX', 'MXHS', 'MXHSPCB', 'X'],
        'led': None,
        'diode': False,
        'symbol': {
            'name': 'KEYSWITCH-PLAIN',
            'description': 'Keyboard switch without LEDs.',
            'wires': switch_symbol_outline,
            'labels': switch_symbol_labels,
            'pins': switch_pins,
        },
    },
    'PLATE': {
        'switch_types': ['ALPSPLATE', 'ALPSMXPLATE', 'MXPLATE'],
        'led': None,
        'diode': False,
        'symbol': {
            'name': 'KEYSWITCH-PLATE',
            'description': 'Keyboard switch cutout for FR4 plates.',
            'wires': switch_symbol_outline,
            'labels': switch_symbol_labels,
            'pins': [],
        },
    },
    'LED': {
        'switch_types': ['ALPSMX', 'ALPSMXMIR', 'MX'],
        'led': 'single',  # 2 pins, single color LED
        'diode': False,
        'symbol': {
            'name': 'KEYSWITCH-LED',
            'description': 'Keyboard switch with 2 pin LED.',
            'wires': switch_symbol_outline,
            'labels': switch_symbol_labels,
            'pins': switch_pins+switch_led_plus+switch_led_minus,
        },
    },
    'LEDHOLE': {
        'switch_types': ['ALPS', 'ALPSMX', 'ALPSMXMIR', 'MX', 'MXHS', 'MXHSPCB'],
        'led': 'hole',  # A single slot for an add-on board to shine through
        'diode': False,
        'symbol': {
            'name': 'KEYSWITCH-LEDHOLE',
            'description': 'Keyboard switch with hole for LED to shine through.',
            'wires': switch_symbol_outline,
            'labels': switch_symbol_labels,
            'pins': switch_pins,
        },
    },
    'LEDTHTHOLE': {
        'switch_types': ['ALPS', 'ALPSMX', 'ALPSMXMIR', 'MX', 'MXHS', 'MXHSPCB'],
        'led': 'tht-hole',  # A single slot for an add-on board to shine through
        'diode': False,
        'symbol': {
            'name': 'KEYSWITCH-LEDTHTHOLE',
            'description': 'Keyboard switch with 2 pin LED and a slot for LED to shine through.',
            'wires': switch_symbol_outline,
            'labels': switch_symbol_labels,
            'pins': switch_pins+switch_led_plus+switch_led_minus,
        },
    },
    'RGBLED': {
        'switch_types': ['ALPSMX', 'ALPSMXMIR', 'MX'],
        'led': 'rgb',  # 4 pins, RGB LED
        'diode': False,
        'symbol': {
            'name': 'KEYSWITCH-RGBLED',
            'description': 'Keyboard switch with 4-pin RGB LED support.',
            'wires': switch_symbol_outline,
            'labels': switch_symbol_labels,
            'pins': switch_pins+switch_led_plus+switch_led_rgb,
        },
    },
    'RGBSMDLED': {
        'switch_types': ['ALPS', 'ALPSMX', 'ALPSMXMIR', 'MX', 'MXHS', 'MXHSPCB'],
        'led': 'rgb-smd',  # 4 pins, RGB LED, SMD shining through PCB
        'diode': False,
        'symbol': {
            'name': 'KEYSWITCH-RGBSMDLED',
            'description': 'Keyboard switch with 4 pin SMD RGB LED support.',
            'wires': switch_symbol_outline,
            'labels': switch_symbol_labels,
            'pins': switch_pins+switch_led_plus+switch_led_rgb,
        },
    },
    'SMDLED': {
        'switch_types': ['ALPSMX', 'ALPSMXMIR', 'MX', 'MXHS', 'MXHSPCB'],
        'led': 'single-smd',  # 2 pins, single color SMD LED
        'diode': False,
        'symbol': {
            'name': 'KEYSWITCH-SMDLED',
            'description': 'Keyboard switch with 2 pin SMD LED support.',
            'wires': switch_symbol_outline,
            'labels': switch_symbol_labels,
            'pins': switch_pins+switch_led_plus+switch_led_minus,
        },
    },
    'THTSMDLED': {
        'switch_types': ['ALPSMX', 'ALPSMXMIR', 'MX'],
        'led': 'single-tht-smd',  # 2 pins, single color LED, THT or SMD
        'diode': False,
        'symbol': {
            'name': 'KEYSWITCH-THTSMDLED',
            'description': 'Keyboard switch with 2 pin THT and SMD LED support.',
            'wires': switch_symbol_outline,
            'labels': switch_symbol_labels,
            'pins': switch_pins+switch_led_plus+switch_led_minus,
        },
    },
    'DIODE': {
        'switch_types': ['ALPSMX', 'ALPSMXMIR', 'MX'],
        'led': None,
        'diode': True,
        'symbol': {
            'name': 'KEYSWITCH-DIODE',
            'description': 'Keyboard key switch with 2 pin diode support.',
            'wires': switch_symbol_outline,
            'labels': switch_symbol_labels,
            'pins': switch_pins+switch_diode,
        },
    }
}

template = {
    'description': 'Keyboard Keyswitch PCB footprints for MX and Alps switches.',
    'packages': [],
    'symbols': [],
    'devicesets': []
}
packages = OrderedDict()

# Fill in our template entries
for device in sorted(devices):
    template['symbols'].append(devices[device]['symbol'])
    footprints = []
    for switch_type in devices[device]['switch_types']:
        for key_size in sorted(switch_sizes):
            connections = copy(connects[switch_type])
            footprint_name = '-%s-%sU' % (switch_type, key_size)
            if devices[device]['diode']:
                connections.insert(0, {'gate': 'G$1', 'pin': 'D-', 'pad': 'D-'})
                connections.insert(0, {'gate': 'G$1', 'pin': 'D+', 'pad': 'D+'})
                footprint_name = footprint_name + '-DIODE'
            elif devices[device]['led'] == 'hole':
                footprint_name = footprint_name + '-LEDHOLE'
            elif devices[device]['led'] == 'rgb':
                connections.insert(0, {'gate': 'G$1', 'pin': 'R-', 'pad': 'R-'})
                connections.insert(0, {'gate': 'G$1', 'pin': 'LED+', 'pad': 'LED+'})
                connections.insert(0, {'gate': 'G$1', 'pin': 'G-', 'pad': 'G-'})
                connections.insert(0, {'gate': 'G$1', 'pin': 'B-', 'pad': 'B-'})
                footprint_name = footprint_name + '-RGB'
            elif devices[device]['led'] == 'single':
                connections.insert(0, {'gate': 'G$1', 'pin': 'LED-', 'pad': 'LED-'})
                connections.insert(0, {'gate': 'G$1', 'pin': 'LED+', 'pad': 'LED+'})
                footprint_name = footprint_name + '-LED'
            elif devices[device]['led'] == 'tht-hole':
                connections.insert(0, {'gate': 'G$1', 'pin': 'LED-', 'pad': 'LED-'})
                connections.insert(0, {'gate': 'G$1', 'pin': 'LED+', 'pad': 'LED+'})
                footprint_name = footprint_name + '-LEDTHTHOLE'
            elif devices[device]['led'] == 'single-smd':
                connections.insert(0, {'gate': 'G$1', 'pin': 'LED-', 'pad': 'SMDLED-'})
                connections.insert(0, {'gate': 'G$1', 'pin': 'LED+', 'pad': 'SMDLED+'})
                footprint_name = footprint_name + '-SMDLED'
            elif devices[device]['led'] == 'single-tht-smd':
                connections.insert(0, {'gate': 'G$1', 'pin': 'LED-', 'pad': 'LED- SMDLED-'})
                connections.insert(0, {'gate': 'G$1', 'pin': 'LED+', 'pad': 'LED+ SMDLED+'})
                footprint_name = footprint_name + '-THTSMDLED'
            elif devices[device]['led'] == 'rgb-smd':
                connections.insert(0, {'gate': 'G$1', 'pin': 'R-', 'pad': 'R-'})
                connections.insert(0, {'gate': 'G$1', 'pin': 'LED+', 'pad': 'LED+'})
                connections.insert(0, {'gate': 'G$1', 'pin': 'G-', 'pad': 'G-'})
                connections.insert(0, {'gate': 'G$1', 'pin': 'B-', 'pad': 'B-'})
                footprint_name = footprint_name + '-SMDRGB'
            package_name = footprint_name[1:]
            if '--' in package_name:
                package_name = package_name.replace('--', '-REVERSED-')
            packages[package_name] = copy(devices[device])
            packages[package_name].update({'name': package_name, 'device': device, 'switch_type': switch_type, 'size': key_size, 'style': 'NORMAL'})
            footprints.append({
                'name': footprint_name,
                'package': package_name,
                'connects': connections
            })
            if key_size != '1':
                for style in ('FLIPPED', 'FLIPPED-ROTATED', 'ROTATED'):
                    package = '-'.join((package_name, style))
                    packages[package] = copy(devices[device])
                    packages[package].update({'name': package, 'device': device, 'switch_type': switch_type, 'size': key_size, 'style': style})
                    footprints.append({
                        'name': '-'.join((footprint_name, style)),
                        'package': package,
                        'connects': connections
                    })
    template['devicesets'].append({
        'name': 'KEYSWITCH-' + device,
        'devices': footprints
    })

schematic_script = []
board_script = ['grid mm 19.05;', 'grid alt mm 4.7625;']
current_x = Decimal('0')
current_x_mm = Decimal('0')
current_y = Decimal('0')
current_y_mm = Decimal('0')
last_row = None

for package in packages:
    pkg = packages[package]
    #pprint(pkg)
    current_row = pkg['symbol']['name'] + '-' + pkg['name'].split('-')[0]
    if current_row != last_row:
        current_x = Decimal('0')
        current_x_mm = Decimal('0')
        current_y += Decimal('1.5')
        current_y_mm += Decimal('38.1')
    last_row = current_row
    if 'FLIPPED' in pkg['name']:
        schematic_script.append('ADD *%s-%s %s (%s -%s);' % (pkg['symbol']['name'], pkg['name'], pkg['name'], current_x, current_y + Decimal('0.75')))
        board_script.append('MOVE %s (%s -%s);' % (pkg['name'], current_x_mm, current_y_mm + Decimal('19.05')))
    current_x += Decimal('0.75')
    if 'FLIPPED' not in pkg['name']:
        current_x_mm += Decimal('19.05') * abs(Decimal(pkg['size']))
        schematic_script.append('ADD *%s-%s %s (%s -%s);' % (pkg['symbol']['name'], pkg['name'], pkg['name'], current_x, current_y))
        board_script.append('MOVE %s (%s -%s);' % (pkg['name'], current_x_mm, current_y_mm))

    template['packages'].append({
        'name': pkg['name'],
        'description': 'Keyboard switch package!',
        'wires': copy(package_wires[pkg['switch_type']]),
        'holes': copy(package_holes[pkg['switch_type']]),
        'pads': copy(package_pads[pkg['switch_type']]),
        'smds': copy(package_smds[pkg['switch_type']]),
        'labels': []
    })
    label_offset = '-2.8'
    if pkg['switch_type'] in ['CHOC', 'CHOCX', 'X']:
        template['packages'][-1]['labels'].append({'value': 'LED', 'x': '0', 'y': '-4.8', 'size': '1', 'layer': '47', 'align': 'center'})
        label_offset = '-6.215'
    elif pkg['led'] in ['rgb-smd']:
        label_offset = '-7'
    elif pkg['led'] in ['hole']:
        label_offset = '-3.215'
    template['packages'][-1]['labels'].append({'value': '&gt;NAME', 'x': '0', 'y': label_offset, 'size': '1', 'layer': '21', 'align': 'center'})
    template['packages'][-1]['labels'].append({'value': '&gt;NAME', 'x': '0', 'y': label_offset, 'size': '1', 'layer': '22', 'align': 'center', 'rot': 'MR0'})

    if pkg['diode']:
        template['packages'][-1]['pads'].append({'name': 'D+', 'x': '-3.81', 'y': '-5.08', 'drill': '1', 'diameter': '2'})
        template['packages'][-1]['labels'].append({'value': '+', 'x': '-1.905', 'y': '-5.08', 'size': '1', 'layer': '21', 'align': 'center'})
        template['packages'][-1]['labels'].append({'value': '+', 'x': '-1.905', 'y': '-5.08', 'size': '1', 'layer': '22', 'align': 'center', 'rot': 'MR0'})
        template['packages'][-1]['pads'].append({'name': 'D-', 'x': '3.81', 'y': '-5.08', 'drill': '1', 'diameter': '2', 'shape': 'square'})
        template['packages'][-1]['labels'].append({'value': '-', 'x': '1.905', 'y': '-5.08', 'size': '1', 'layer': '21', 'align': 'center'})
        template['packages'][-1]['labels'].append({'value': '-', 'x': '1.905', 'y': '-5.08', 'size': '1', 'layer': '22', 'align': 'center', 'rot': 'MR0'})
    elif pkg['led'] == 'single':
        template['packages'][-1]['pads'].append({'name': 'LED+', 'x': '-1.27', 'y': '-5.08', 'drill': '1', 'diameter': '2'})
        template['packages'][-1]['labels'].append({'value': '+', 'x': '-3.175', 'y': '-5.08', 'size': '1', 'layer': '21', 'align': 'center'})
        template['packages'][-1]['labels'].append({'value': '+', 'x': '-3.175', 'y': '-5.08', 'size': '1', 'layer': '22', 'align': 'center', 'rot': 'MR0'})
        template['packages'][-1]['pads'].append({'name': 'LED-', 'x': '1.27', 'y': '-5.08', 'drill': '1', 'diameter': '2', 'shape': 'square'})
        template['packages'][-1]['labels'].append({'value': '-', 'x': '3.175', 'y': '-5.08', 'size': '1', 'layer': '21', 'align': 'center'})
        template['packages'][-1]['labels'].append({'value': '-', 'x': '3.175', 'y': '-5.08', 'size': '1', 'layer': '22', 'align': 'center', 'rot': 'MR0'})
    elif pkg['led'] == 'single-smd':
        template['packages'][-1]['smds'].append({'name': 'SMDLED+', 'x': '-1.3', 'y': '-5.75', 'dx': '2', 'dy': '1.75', 'layer': '1'})
        template['packages'][-1]['labels'].append({'value': '+', 'x': '-3.175', 'y': '-5.75', 'size': '1', 'layer': '21', 'align': 'center'})
        template['packages'][-1]['smds'].append({'name': 'SMDLED-', 'x': '1.3', 'y': '-5.75', 'dx': '2', 'dy': '1.75', 'layer': '1'})
        template['packages'][-1]['labels'].append({'value': '-', 'x': '3.175', 'y': '-5.75', 'size': '1', 'layer': '21', 'align': 'center'})
    elif pkg['led'] == 'single-tht-smd':
        template['packages'][-1]['pads'].append({'name': 'LED+', 'x': '-1.27', 'y': '-5.08', 'drill': '1', 'diameter': '2'})
        template['packages'][-1]['labels'].append({'value': '+', 'x': '-3.175', 'y': '-5.08', 'size': '1', 'layer': '21', 'align': 'center'})
        template['packages'][-1]['labels'].append({'value': '+', 'x': '-3.175', 'y': '-5.08', 'size': '1', 'layer': '22', 'align': 'center', 'rot': 'MR0'})
        template['packages'][-1]['pads'].append({'name': 'LED-', 'x': '1.27', 'y': '-5.08', 'drill': '1', 'diameter': '2', 'shape': 'square'})
        template['packages'][-1]['labels'].append({'value': '-', 'x': '3.175', 'y': '-5.08', 'size': '1', 'layer': '21', 'align': 'center'})
        template['packages'][-1]['labels'].append({'value': '-', 'x': '3.175', 'y': '-5.08', 'size': '1', 'layer': '22', 'align': 'center', 'rot': 'MR0'})
        template['packages'][-1]['smds'].append({'name': 'SMDLED+', 'x': '-1.3', 'y': '-6.785', 'dx': '2', 'dy': '1.3', 'layer': '1'})
        template['packages'][-1]['labels'].append({'value': '+', 'x': '-3.175', 'y': '-6.785', 'size': '1', 'layer': '21', 'align': 'center'})
        template['packages'][-1]['smds'].append({'name': 'SMDLED-', 'x': '1.3', 'y': '-6.785', 'dx': '2', 'dy': '1.3', 'layer': '1'})
        template['packages'][-1]['labels'].append({'value': '-', 'x': '3.175', 'y': '-6.785', 'size': '1', 'layer': '21', 'align': 'center'})
    elif pkg['led'] == 'rgb-smd':
        template['packages'][-1]['holes'].append({'x': '0', 'y': '-4.5', 'diameter': '2.4'})
        template['packages'][-1]['smds'].append({'name': 'LED+', 'x': '2.1', 'y': '-3.775', 'dx': '1', 'dy': '0.75', 'layer': '16'})
        template['packages'][-1]['smds'].append({'name': 'R-', 'x': '-2.1', 'y': '-3.775', 'dx': '1', 'dy': '0.75', 'layer': '16'})
        template['packages'][-1]['smds'].append({'name': 'G-', 'x': '-2.1', 'y': '-5.225', 'dx': '1', 'dy': '0.75', 'layer': '16'})
        template['packages'][-1]['smds'].append({'name': 'B-', 'x': '2.1', 'y': '-5.225', 'dx': '1', 'dy': '0.75', 'layer': '16'})
        template['packages'][-1]['wires'].append({'x1': '-1.6', 'y1': '-5.9', 'x2': '-1.6', 'y2': '-3.9', 'width': '0.125', 'layer': '22'})
        template['packages'][-1]['wires'].append({'x1': '-0.8', 'y1': '-3.1', 'x2': '-1.6', 'y2': '-3.9', 'width': '0.125', 'layer': '22'})
        template['packages'][-1]['wires'].append({'x1': '-0.8', 'y1': '-3.1', 'x2': '1.6', 'y2': '-3.1', 'width': '0.125', 'layer': '22'})
        template['packages'][-1]['wires'].append({'x1': '1.6', 'y1': '-3.1', 'x2': '1.6', 'y2': '-5.9', 'width': '0.125', 'layer': '22'})
        template['packages'][-1]['wires'].append({'x1': '1.6', 'y1': '-5.9', 'x2': '-1.6', 'y2': '-5.9', 'width': '0.125', 'layer': '22'})
    elif pkg['led'] == 'rgb':
        template['packages'][-1]['pads'].append({'name': 'R-', 'x': '-3.81', 'y': '-5.08', 'drill': '1', 'diameter': '2'})
        template['packages'][-1]['labels'].append({'value': 'R-', 'x': '-3.955', 'y': '-6.985', 'size': '1', 'layer': '21', 'align': 'center'})
        template['packages'][-1]['labels'].append({'value': 'R-', 'x': '-3.955', 'y': '-6.985', 'size': '1', 'layer': '22', 'align': 'center', 'rot': 'MR0'})
        template['packages'][-1]['pads'].append({'name': 'LED+', 'x': '-1.27', 'y': '-5.08', 'drill': '1', 'diameter': '2', 'shape': 'square'})
        template['packages'][-1]['labels'].append({'value': '+', 'x': '-1.125', 'y': '-6.985', 'size': '1', 'layer': '21', 'align': 'center'})
        template['packages'][-1]['labels'].append({'value': '+', 'x': '-1.125', 'y': '-6.985', 'size': '1', 'layer': '22', 'align': 'center', 'rot': 'MR0'})
        template['packages'][-1]['pads'].append({'name': 'G-', 'x': '1.27', 'y': '-5.08', 'drill': '1', 'diameter': '2'})
        template['packages'][-1]['labels'].append({'value': 'G-', 'x': '1.125', 'y': '-6.985', 'size': '1', 'layer': '21', 'align': 'center'})
        template['packages'][-1]['labels'].append({'value': 'G-', 'x': '1.125', 'y': '-6.985', 'size': '1', 'layer': '22', 'align': 'center', 'rot': 'MR0'})
        template['packages'][-1]['pads'].append({'name': 'B-', 'x': '3.81', 'y': '-5.08', 'drill': '1', 'diameter': '2'})
        template['packages'][-1]['labels'].append({'value': 'B-', 'x': '3.955', 'y': '-6.985', 'size': '1', 'layer': '21', 'align': 'center'})
        template['packages'][-1]['labels'].append({'value': 'B-', 'x': '3.955', 'y': '-6.985', 'size': '1', 'layer': '22', 'align': 'center', 'rot': 'MR0'})
    elif pkg['led'] == 'hole':
        template['packages'][-1]['wires'].append({'x1': '-4.31', 'y1': '-4.83', 'x2': '-3.81', 'y2': '-4.33', 'width': '0', 'layer': '20', 'curve': '-90'})
        template['packages'][-1]['wires'].append({'x1': '-3.81', 'y1': '-4.33', 'x2': '3.81', 'y2': '-4.33', 'width': '0', 'layer': '20'})
        template['packages'][-1]['wires'].append({'x1': '3.81', 'y1': '-4.33', 'x2': '4.31', 'y2': '-4.83', 'width': '0', 'layer': '20', 'curve': '-90'})
        template['packages'][-1]['wires'].append({'x1': '4.31', 'y1': '-4.83', 'x2': '4.31', 'y2': '-5.33', 'width': '0', 'layer': '20'})
        template['packages'][-1]['wires'].append({'x1': '4.31', 'y1': '-5.33', 'x2': '3.81', 'y2': '-5.83', 'width': '0', 'layer': '20', 'curve': '-90'})
        template['packages'][-1]['wires'].append({'x1': '3.81', 'y1': '-5.83', 'x2': '-3.81', 'y2': '-5.83', 'width': '0', 'layer': '20'})
        template['packages'][-1]['wires'].append({'x1': '-3.81', 'y1': '-5.83', 'x2': '-4.31', 'y2': '-5.33', 'width': '0', 'layer': '20', 'curve': '-90'})
        template['packages'][-1]['wires'].append({'x1': '-4.31', 'y1': '-5.33', 'x2': '-4.31', 'y2': '-4.83', 'width': '0', 'layer': '20'})
    elif pkg['led'] == 'tht-hole':
        template['packages'][-1]['pads'].append({'name': 'LED+', 'x': '-1.27', 'y': '-5.08', 'drill': '1', 'diameter': '2'})
        template['packages'][-1]['labels'].append({'value': '+', 'x': '-3.175', 'y': '-5.08', 'size': '1', 'layer': '21', 'align': 'center'})
        template['packages'][-1]['labels'].append({'value': '+', 'x': '-3.175', 'y': '-5.08', 'size': '1', 'layer': '22', 'align': 'center', 'rot': 'MR0'})
        template['packages'][-1]['pads'].append({'name': 'LED-', 'x': '1.27', 'y': '-5.08', 'drill': '1', 'diameter': '2', 'shape': 'square'})
        template['packages'][-1]['labels'].append({'value': '-', 'x': '3.175', 'y': '-5.08', 'size': '1', 'layer': '21', 'align': 'center'})
        template['packages'][-1]['labels'].append({'value': '-', 'x': '3.175', 'y': '-5.08', 'size': '1', 'layer': '22', 'align': 'center', 'rot': 'MR0'})
        template['packages'][-1]['wires'].append({'x1':'-0.8', 'y1':'-4.58', 'x2':'-0.3', 'y2':'-4.08', 'width':'0', 'layer':'20', 'curve':'-90'})
        template['packages'][-1]['wires'].append({'x1':'-0.3', 'y1':'-4.08', 'x2':'0.3', 'y2':'-4.08', 'width':'0', 'layer':'20'})
        template['packages'][-1]['wires'].append({'x1':'0.3', 'y1':'-4.08', 'x2':'0.8', 'y2':'-4.58', 'width':'0', 'layer':'20', 'curve':'-90'})
        template['packages'][-1]['wires'].append({'x1':'0.8', 'y1':'-4.58', 'x2':'0.8', 'y2':'-5.58', 'width':'0', 'layer':'20'})
        template['packages'][-1]['wires'].append({'x1':'0.8', 'y1':'-5.58', 'x2':'0.3', 'y2':'-6.08', 'width':'0', 'layer':'20', 'curve':'-90'})
        template['packages'][-1]['wires'].append({'x1':'0.3', 'y1':'-6.08', 'x2':'-0.3', 'y2':'-6.08', 'width':'0', 'layer':'20'})
        template['packages'][-1]['wires'].append({'x1':'-0.3', 'y1':'-6.08', 'x2':'-0.8', 'y2':'-5.58', 'width':'0', 'layer':'20', 'curve':'-90'})
        template['packages'][-1]['wires'].append({'x1':'-0.8', 'y1':'-5.58', 'x2':'-0.8', 'y2':'-4.58', 'width':'0', 'layer':'20'})

    if pkg['size'] != '1':
        c = switch_sizes[pkg['size']]
        if pkg['style'] == 'FLIPPED':
            template['packages'][-1]['holes'].append({'x': c['lstab'], 'y': -c['tstab'], 'diameter': '3.05'})
            template['packages'][-1]['holes'].append({'x': c['rstab'], 'y': -c['tstab'], 'diameter': '3.05'})
            template['packages'][-1]['holes'].append({'x': c['lstab'], 'y': -c['bstab'], 'diameter': '4'})
            template['packages'][-1]['holes'].append({'x': c['rstab'], 'y': -c['bstab'], 'diameter': '4'})
        elif pkg['style'] == 'FLIPPED-ROTATED':
            template['packages'][-1]['holes'].append({'y': c['lstab'], 'x': -c['tstab'], 'diameter': '3.05'})
            template['packages'][-1]['holes'].append({'y': c['rstab'], 'x': -c['tstab'], 'diameter': '3.05'})
            template['packages'][-1]['holes'].append({'y': c['lstab'], 'x': -c['bstab'], 'diameter': '4'})
            template['packages'][-1]['holes'].append({'y': c['rstab'], 'x': -c['bstab'], 'diameter': '4'})
        elif pkg['style'] == 'ROTATED':
            template['packages'][-1]['holes'].append({'y': c['lstab'], 'x': c['tstab'], 'diameter': '3.05'})
            template['packages'][-1]['holes'].append({'y': c['rstab'], 'x': c['tstab'], 'diameter': '3.05'})
            template['packages'][-1]['holes'].append({'y': c['lstab'], 'x': c['bstab'], 'diameter': '4'})
            template['packages'][-1]['holes'].append({'y': c['rstab'], 'x': c['bstab'], 'diameter': '4'})
        else:
            template['packages'][-1]['holes'].append({'x': c['lstab'], 'y': c['tstab'], 'diameter': '3.05'})
            template['packages'][-1]['holes'].append({'x': c['rstab'], 'y': c['tstab'], 'diameter': '3.05'})
            template['packages'][-1]['holes'].append({'x': c['lstab'], 'y': c['bstab'], 'diameter': '4'})
            template['packages'][-1]['holes'].append({'x': c['rstab'], 'y': c['bstab'], 'diameter': '4'})

if __name__ == '__main__':
    t = Template(open('Keyboard.lbr.jinja2').read())
    with open('Keyboard.lbr', 'w') as fd:
        fd.seek(0, 0)
        fd.write(t.render(**template))

    #print('*** You can use this script to add every single footprint to a schematic:')
    #print('\n'.join(schematic_script))
    #print('\n\n\n\n\n')
    #print('*** You can use this script to place every single footprint on a board:')
    #print('\n'.join(board_script))
