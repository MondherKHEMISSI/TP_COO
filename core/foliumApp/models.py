from django.db import models

class Departement(models.Model):
    departement_name = models.CharField(max_length=250)
    zip_code = models.CharField(max_length=10)
    price_m2 = models.CharField(max_length=20)
    meteo = models.CharField(max_length=20, default='', blank=True)

    def __str__(self):
        return self.departement_name