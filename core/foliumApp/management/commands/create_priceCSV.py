import csv
from django.conf import settings
from django.core.management.base import BaseCommand
from foliumApp.models import Departement


class Command(BaseCommand):
    help = 'Write data to Price m2 file'

    def handle(self, *args, **kwargs):
        departements = Departement.objects.all()
        
        # csv header
        fieldnames = ['departement_name', 'price_m2', 'zip_code', 'meteo']


        with open('prices.csv', 'w', encoding='UTF8', newline='') as f:
            writer = csv.DictWriter(f, fieldnames=fieldnames)
            writer.writeheader()
            for departement in departements:
                writer.writerow({'departement_name': departement.departement_name, 
                                 'price_m2': departement.price_m2,
                                 'zip_code': departement.zip_code,
                                 'meteo': departement.meteo
                                })