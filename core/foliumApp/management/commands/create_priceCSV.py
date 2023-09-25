import csv
from django.conf import settings
from django.core.management.base import BaseCommand
from foliumApp.models import Prices


class Command(BaseCommand):
    help = 'Write data to Price m2 file'

    def handle(self, *args, **kwargs):
        departements = Prices.objects.all()
        
        # csv header
        fieldnames = ['departement_name', 'price']


        with open('prices.csv', 'w', encoding='UTF8', newline='') as f:
            writer = csv.DictWriter(f, fieldnames=fieldnames)
            writer.writeheader()
            for departement in departements:
                writer.writerow({'departement_name': departement.departement_name, 
                                 'price': departement.price})