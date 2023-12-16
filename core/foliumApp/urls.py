from django.urls import path

from . import views
from .views import (
    ActionDetailView,
    DepartementDetailView,
    FactoryDetailView,
    IngredientDetailView,
    IngredientQuantityDetailView,
    IngredientQuantityUpdateView,
    MachineDetailView,
    PriceDetailView,
    RecipeDetailView,
    SaleCreateView,
)

urlpatterns = [
    path("", views.index, name="index"),
    path(
        "departement/<int:pk>/",
        DepartementDetailView.as_view(),
        name="departement_detail",
    ),
    path("machine/<int:pk>/", MachineDetailView.as_view(), name="machine_detail"),
    path("factory/<int:pk>/", FactoryDetailView.as_view(), name="factory_detail"),
    path(
        "ingredient/<int:pk>/", IngredientDetailView.as_view(), name="ingredient_detail"
    ),
    path(
        "ingredientquantity/<int:pk>/",
        IngredientQuantityDetailView.as_view(),
        name="ingredientquantity_detail",
    ),
    path("price/<int:pk>/", PriceDetailView.as_view(), name="price_detail"),
    path("recipe/<int:pk>/", RecipeDetailView.as_view(), name="recipe_detail"),
    path("action/<int:pk>/", ActionDetailView.as_view(), name="action_detail"),
    path("sale/", SaleCreateView.as_view(), name="sale_detail"),
    path(
        "ingredientquantity/",
        IngredientQuantityUpdateView.as_view(),
        name="ingredientquantity_detail",
    ),
]
