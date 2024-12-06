def calculate_crc(data):
    crc = 0xFFFF
    for byte in data:
        crc ^= byte
        for _ in range(8):
            if crc & 0x0001:
                crc >>= 1
                crc ^= 0xA001
            else:
                crc >>= 1
    # Return as (low byte, high byte)
    return crc & 0xFF, (crc >> 8) & 0xFF

# Example: Calculate CRC for [0x01, 0x03, 0x00, 0x1E, 0x00, 0x01]
request_frame = [0x01, 0x03, 0x07, 0xD1, 0x00, 0x01]
crc_low, crc_high = calculate_crc(request_frame)
print(f"CRC: Low Byte = 0x{crc_low:02X}, High Byte = 0x{crc_high:02X}")
