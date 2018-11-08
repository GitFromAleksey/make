# -*- coding: utf-8 -*-

import sys
import os.path
import struct
import ctypes
import binascii
import zlib

from intelhex import bin2hex


def crc(words_lst):
    r = zlib.crc32(struct.pack('>{}L'.format(len(words_lst)), *words_lst))
    return ctypes.c_uint32(r).value, ctypes.c_uint32(~r).value


def main():

#     dat = [0x0, 0xb3590070, 0, 0, 0, 0]
#     bmh_addr = 0xA0000000
#     user_start_addr = 0xA0000020
#     lockstep0_en = 0
#     pindis = 0  # must be always zero to have recovery backdoor opened

    bmh_addr = 0xA0000000
    user_start_addr = 0xA0080000
    lockstep0_en = 1
    pindis = 0  # must be always zero to have recovery backdoor opened

    bmi_lcl0lsen = 1 if lockstep0_en else 0
    if user_start_addr == 0xA0000020:
        abm = False
        bmh_start_addr_abm = 0
        bmi_hwcfg = 0x7
    else:
        abm = True
        bmh_start_addr_abm = user_start_addr
        bmi_hwcfg = 0x6
    bmi = (bmi_lcl0lsen << 8) | (bmi_hwcfg << 4)
    dat = [bmh_start_addr_abm, 0xB3590000 | bmi]
    if abm:
        # trick to get valid user range and crc value
        crc_chk_val = crc(dat)
        # crc_chk_range 
        dat.extend([bmh_addr, bmh_addr + struct.calcsize('L') * (len(dat) - 1)])
        dat.extend(crc_chk_val)
    else:
        dat.extend(4 * [0])
    bmh_crc = crc(dat)
    dat.extend(bmh_crc)
    bmh_bytes = struct.pack('<{}L'.format(len(dat)), *dat)
    print binascii.hexlify(bmh_bytes)

    fn = '../output/bmh.hex'
    with file(fn, 'wb') as out_file:
        out_file.write(bmh_bytes)

    bin2hex(fn, fn, bmh_addr)

    return 0


if __name__ == '__main__':
    sys.exit(main())
