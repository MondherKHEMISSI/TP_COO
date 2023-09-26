import csv
from django.conf import settings
from django.core.management.base import BaseCommand
from foliumApp.models import Departement


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

        
        for record in records:
            departement_name = record['Département'].split(" ")[0]
            zip_code = record['Département'].split(" ")[1].split("(")[1].split(")")[0]
            record['Département'] = departement_name
            record['zip_code'] = zip_code
            

            # add the data to the database
            Departement.objects.get_or_create(
                departement_name=record['Département'],
                zip_code=record['zip_code'],
                price_m2=record['€/m²'] + ' €',
            )