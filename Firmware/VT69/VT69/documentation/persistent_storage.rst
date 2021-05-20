Persistent Storage
==================

Persistent storage is middle-ware which provides means for storing data in non-volatile memory.

In terms of persistent storage stored data is called an item. Different items must have different IDs. IDs must be unique
and start with value of 1.
If an item is written two or more times, previous values get "overwritten" (read access returns the latest written data).

The usual use-case of persistent storage is an attempt to restore previously stored items on start-up.
For that, nv_storage_init function must be called. This function scans non-volatile memory starting from the given address
looking for items to restore. If there is a valid storage, the persistent storage initializes internal structures and gets
prepared for upcoming read (or write) accesses. If no valid storage found, the persistent storage tries to create one by
writing a header with storage information.

When an item is written the first item, it is being created inside the storage. In this case "offset" parameter is
ignored and the item is created with the given size. Re-sizing of items is not allowed, attempts to write more data than
item size or outside of an item (offset + size in write access is bigger than initial size) will fail.

Features
--------

* Power failure protection
* Wear-leveling
* Writing/reading parts of stored items
* Possibility to work with different types of non-volatile memory

Architecture and provided functionality
---------------------------------------

The persistent storage is composed of two layers:

* NV storage

This is the upper layer which contains implementation of wear-leveling, partial write and power failure protection
algorithms.

The partial write/read access allows to write/read parts of previously written items. For example, it is possible to read
first N bytes, or last N bytes, or N bytes from the middle of stored item.
Read operation always returns the latest successfully written data, it applies for partial write too. For example, if
partial write access stores M first bytes of the item of length of N (N > M), then read operation returns data that
contains M first bytes from partial write, and N-M last bytes from initial write.

The writing of an item or its part is split into three write accesses, after each it is validated whether the data was
written correctly by reading it out and comparing with the content of an item in RAM. It is required to be able to detect
whether data was written correctly if a power failure happens during writing procedure. This detection happens during
storage initialization (nv_storage_init function). In case of detection of invalid item, previous successfully written
item, if any, is used.

The area in non-volatile memory allocated for the persistent storage is split to at least (by default) two sectors.
Each write operation writes data to a new position in one of the sectors, gradually filling it up. When the sector is
full, the persistent storage can detect this fact during write/delete access. Upon detection, before actual write,
sector compression is performed. During the compression each of the stored items is gathered into one item (if there were
partial writes accesses) and copied to another sector. After all the items are copied, new sector is activated and
previous sector is erased.
The level of wearing non-volatile memory out can be tuned by adjusting the size of the area allocated for the persistent
storage.

Usually writing to non-volatile memory is a slow process, the sector compression may take significant time. The persistent
storage provides function (nv_storage_force_packing) to allow applications to perform the compression at the time suitable
for the application.

* Wrapper

This is the lower layer which is basically a wrapper between API expected by the upper layer and driver/middle-ware used
to work with non-volatile memory. At the moment, only internal flash on SAMD/SAML/SAMR/SAMC devices is supported.

Dependencies
------------

Flash driver on SAMD/SAML/SAMR/SAMC devices.

Limitations
-----------

Due to the architecture of the flash memory on SAMD/SAML/SAMR/SAMC devices, which allows only 8 writes before flash row
must be erase for the next write, each write of an item or a part of an item is aligned by 128 bytes.

Currently only internal flash memory on SAMD/SAML/SAMR/SAMC devices is supported.
It is user's responsibility to modify the linker script to reserve section in flash for the storage. Its start address
should match the address provided in the persistent storage configuration, its size should be equal to the sector size
multiplied by sectors amount (2 by default).
