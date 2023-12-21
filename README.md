# Brewsim Project
============

Dans un terminal, sélectionnez d'abord un répertoire de travail, puis collez ces commandes:

    git clone git@github.com:MondherKHEMISSI/TP_COO.git

    cd TP_COO

    python3 -m venv .env

    source .env/bin/activate

    pip3 install -r requirements.txt

    cd core

    ./manage.py runserver

Ouvrez un nouveau terminal, placez-vous d'abord dans le répertoire de travail contenant le dossier TP_COO, puis collez ces commandes:

    cd <project directory>/TP_COO

    source .env/bin/activate

    cd low_level

    cmake -B /tmp/build -S . -DCMAKE_CXX_STANDARD=17

    cmake --build /tmp/build

    /tmp/build/low_level
