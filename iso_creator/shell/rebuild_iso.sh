#!/bin/bash

CDROM_DIR=/mnt/cdrom
ISO_DIR=/mnt/create_iso/disk

# generate my own tar bar
EXEC_DIR=$(dirname `readlink -f $0`)
cd $EXEC_DIR

tar -czf ${ISO_DIR}/features.tar.gz features/

# regenerate repo file
cd ${ISO_DIR}

declare -x discinfo=$(head -1 .discinfo)
mv ${ISO_DIR}/repodata/*x86_64-comps.xml ${ISO_DIR}/repodata/c6-x86_64-comps.xml
createrepo -g repodata/c6-x86_64-comps.xml ./
echo "discinfo is $discinfo"

mv ${ISO_DIR}/repodata/*x86_64-comps.xml ${ISO_DIR}/repodata/c6-x86_64-comps.xml
createrepo -u "media://$discinfo" -g ${ISO_DIR}/repodata/*c6-x86_64-comps.xml ${ISO_DIR}


# generate iso file
cd ${ISO_DIR}

mkisofs -o /mnt/create_iso/my-centos-6.6_x64.iso -b isolinux/isolinux.bin -c isolinux/boot.cat -no-emul-boot -boot-load-size 4 -boot-info-table -R -J -v -V -T ${ISO_DIR}
