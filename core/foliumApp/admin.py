from django.contrib import admin

from .models import (
    Action,
    Departement,
    Factory,
    Ingredient,
    IngredientQuantity,
    Machine,
    Price,
    Recipe,
    Sale,
)

admin.site.register(Departement)
admin.site.register(Factory)
admin.site.register(Machine)
admin.site.register(Price)
admin.site.register(Ingredient)
admin.site.register(IngredientQuantity)
admin.site.register(Action)
admin.site.register(Recipe)
admin.site.register(Sale)
