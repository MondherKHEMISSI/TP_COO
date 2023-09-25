from django.db import models

class Prices(models.Model):
    departement_name = models.CharField(max_length=250)
    price = models.IntegerField()

    def __str__(self):
        return self.departement_name