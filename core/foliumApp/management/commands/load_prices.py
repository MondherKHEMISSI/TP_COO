import csv
from django.conf import settings
from django.core.management.base import BaseCommand
from foliumApp.models import Prices


class Command(BaseCommand):
    help = 'Load data from Price m2 file'

    def handle(self, *args, **kwargs):
        data_file = settings.BASE_DIR / 'data' / 'prix_m2.csv'
        keys = ('Département', '€/m²')  # the CSV columns we will gather data from.
        
        records = []
        with open(data_file, 'r') as csvfile:
            reader = csv.DictReader(csvfile)
            for row in reader:
                records.append({k: row[k] for k in keys})

        # extract the departement name
        for record in records:
            departement_name = record['Département'].split(" ")[0]
            record['Département'] = departement_name
            

            # add the data to the database
            Prices.objects.get_or_create(
                departement_name=record['Département'],
                price=record['€/m²'],
            )