from typing import List, AnyStr


def bytes_to_bin(x: bytes, num_bits: int = 8):
    x_num_bits = len(x) * 8
    ret = ''.join([f'{(int(bin(i)[2:])):08d}' for i in x])
    if x_num_bits < num_bits:
        return '0' * (num_bits - x_num_bits) + ret
    else:
        return ret


def bytes_to_binlist(x: bytes, num_bits: int = 8):
    x_num_bits = len(x) * 8
    ret = ''.join([f'{(int(bin(i)[2:])):08d}' for i in x])
    if x_num_bits < num_bits:
        return list('0' * (num_bits - x_num_bits) + ret)
    else:
        return list(ret)


def bytes_to_int(x: bytes) -> int:
    return int.from_bytes(x, 'big')


def binlist_to_int(x: List[AnyStr]):
    return int(''.join(x), base=2)


def binlist_to_bytes(x: List[AnyStr]):
    assert len(x) % 8 == 0
    return int_to_bytes(int(''.join(x), base=2), num_bytes=int(len(x) / 8))


def int_to_binlist(x: int, num_bits: int = 4):
    x = bin(x)[2:]
    x_num_bits = len(x)
    bin_format = f'{{:0{num_bits:d}d}}'
    if x_num_bits >= num_bits:
        bin_format = f'{{:0{x_num_bits:d}d}}'
    return list(bin_format.format(int(x)))


def int_to_bytes(x: int, num_bytes: int = 1) -> bytes:
    return int.to_bytes(x, num_bytes, 'big')
