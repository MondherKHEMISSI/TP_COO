import csv

from django.conf import settings
from django.core.management.base import BaseCommand

from foliumApp.models import Departement


class Command(BaseCommand):
    help = "Load data from long-lat file"

    def handle(self, *args, **kwargs):
        data_file = settings.BASE_DIR / "data" / "long-lat.csv"
        keys = (
            "N°",
            "LONGITUDE",
            "LATITUDE",
        )  # the CSV columns we will gather data from.

        records = []
        with open(data_file, "r") as csvfile:
            reader = csv.DictReader(csvfile)
            for row in reader:
                records.append({k: row[k] for k in keys})

        for record in records:
            # add the data to the database
            Departement.objects.filter(zip_code=record["N°"]).update(
                longitude=record["LONGITUDE"], latitude=record["LATITUDE"]
            )
