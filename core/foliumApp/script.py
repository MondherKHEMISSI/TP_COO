import requests


def getData(id):
    url = f"http://127.0.0.1:8000/factory/{id}"
    data = requests.get(url)

    if data.status_code == 200:
        return data.json()
    else:
        print(f"Error: {data.status_code}")
