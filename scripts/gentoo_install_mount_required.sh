mount /dev/sda1 /mnt/gentoo/boot
mount -t proc none /mnt/gentoo/proc
mount --rbind /dev /mnt/gentoo/dev
echo done
chroot /mnt/gentoo /bin/bash
