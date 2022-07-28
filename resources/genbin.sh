#!/usr/bin/env bash
echo "#!/usr/bin/env bash
export LD_LIBRARY_PATH="\"$LD_LIBRARY_PATH:${1}/lib\""
/opt/img2txt/Img2Txt" > img2txt
chmod +x img2txt
