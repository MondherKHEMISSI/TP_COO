# Brewsim Project
============

Dans un terminal :

    git clone git@github.com:MondherKHEMISSI/TP_COO.git

    cd TP_COO

    python3 -m venv .env

    source .env/bin/activate

    pip3 install -r requirements.txt

    cd core

    ./manage.py runserver

Dans un nouveau terminal :

    cd ~/TP_COO/lowel_level

    cmake -B /tmp/build -S . -DCMAKE_CXX_STANDARD=17

    cmake --build /tmp/build
    
    /tmp/build/low_level
    


