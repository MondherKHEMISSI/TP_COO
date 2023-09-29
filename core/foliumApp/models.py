from django.db import models


class Departement(models.Model):
    name = models.CharField(max_length=250)
    zip_code = models.CharField(max_length=10)
    price_m2 = models.CharField(max_length=20)
    meteo = models.CharField(max_length=20, default="", blank=True)

    def __str__(self):
        return self.name

    def costs(self):
        return int(self.price_m2.split(" ")[0])


class Machine(models.Model):
    name = models.CharField(max_length=250)
    price = models.CharField(max_length=20)

    def __str__(self):
        return self.name

    def costs(self):
        return int(self.price.split(" ")[0])


class Ingredient(models.Model):
    name = models.CharField(max_length=250)

    def __str__(self):
        return self.name


class IngredientQuantity(models.Model):
    ingredient = models.ForeignKey(Ingredient, on_delete=models.PROTECT)
    quantity = models.CharField(max_length=50)

    def __str__(self):
        return f"{self.ingredient}: {self.quantity}"

    def costs(self, zip_code):
        ingredientCost = int(self.quantity.split(" ")[0]) * int(
            self.ingredient.price_set.get(
                departement_name__zip_code=zip_code
            ).price.split(" ")[0]
        )

        return ingredientCost


class Price(models.Model):
    departement_name = models.ForeignKey(Departement, on_delete=models.PROTECT)
    ingredient = models.ForeignKey(Ingredient, on_delete=models.PROTECT)
    price = models.CharField(max_length=50)

    def __str__(self):
        return self.price

    def costs(self):
        pass


class Action(models.Model):
    machine = models.ForeignKey(Machine, on_delete=models.PROTECT)
    command = models.CharField(max_length=50)
    duration = models.CharField(max_length=50)
    ingredient = models.ManyToManyField(IngredientQuantity)
    action = models.CharField(max_length=250)

    def __str__(self):
        return self.action


class Recipe(models.Model):
    name = models.CharField(max_length=250)
    action = models.ForeignKey(Action, on_delete=models.PROTECT)

    def __str__(self):
        return self.name


class Factory(models.Model):
    name = models.CharField(max_length=250)
    area = models.CharField(max_length=50)
    departement = models.ForeignKey(Departement, on_delete=models.PROTECT)
    machines = models.ManyToManyField(Machine)
    recipes = models.ManyToManyField(Recipe)
    stocks = models.ManyToManyField(IngredientQuantity)

    def __str__(self):
        return self.name

    def costs(self):
        machineCost = 0
        areaCost = int(self.area.split(" ")[0]) * self.departement.costs()
        for machine in self.machines.all():
            machineCost += machine.costs()

        stocksCost = 0
        for ingredient in self.stocks.all():
            stocksCost += ingredient.costs(self.departement.zip_code)

        return machineCost + areaCost + stocksCost
