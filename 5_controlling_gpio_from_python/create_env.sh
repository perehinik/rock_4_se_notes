set -e

sudo apt-get install python3 python3-venv python3-pip;

if [ ! -d "./venv" ]; then
  python3 -m venv ./venv;
fi;

. ./venv/bin/activate;

./venv/bin/pip3 install -r ./requirements.txt;

deactivate;
