# Create your tests here.

from django.test import TestCase

from .models import Departement, Factory, Ingredient, IngredientQuantity, Machine, Price


class MachineModelTests(TestCase):
    def setUp(self):
        hauteGaronne = Departement.objects.create(
            name="Haute-Garonne", zip_code="31", price_m2="2000 €"
        )

        Machine.objects.create(name="four", price="2000 €")

        Machine.objects.create(name="malaxeur", price="1000 €")

        houblon = Ingredient.objects.create(name="houblon")
        orge = Ingredient.objects.create(name="orge")

        Price.objects.create(
            ingredient=houblon, departement_name=hauteGaronne, price="20 €/kg"
        )

        Price.objects.create(
            ingredient=orge, departement_name=hauteGaronne, price="10 €/kg"
        )

        IngredientQuantity.objects.create(ingredient=houblon, quantity="50 kg")

        IngredientQuantity.objects.create(ingredient=orge, quantity="100 kg")

        fac = Factory.objects.create(
            name="La Rose", area="50 m2", departement=hauteGaronne
        )

        fac.machines.create(name="malaxeur", price="1000 €")
        fac.machines.create(name="four", price="2000 €")

        fac.stocks.create(ingredient=houblon, quantity="50 kg")

        fac.stocks.create(ingredient=orge, quantity="100 kg")

    def test_factory_creation(self):
        totalCosts = 0
        factories = Factory.objects.all()
        for factory in factories:
            totalCosts += factory.costs()

        self.assertEqual(totalCosts, 105000)
