import json

import folium
import pandas
import requests
from django.conf import settings
from django.http import JsonResponse
from django.shortcuts import render
from django.utils.decorators import method_decorator
from django.views.decorators.csrf import csrf_exempt
from django.views.generic.detail import DetailView
from django.views.generic.edit import CreateView, UpdateView
from dotenv import load_dotenv

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

load_dotenv()

# Choose to render regions or departements
"""
    # Régions
    https://france-geojson.gregoiredavid.fr/repo/regions.geojson

    # Départements
    https://france-geojson.gregoiredavid.fr/repo/departements.geojson

"""


# CreateView
@method_decorator(csrf_exempt, name="dispatch")
class SaleCreateView(CreateView):
    model = Sale
    fields = ["departement", "profit"]

    def post(self, request, *args, **kwargs):
        data = json.loads(request.body)
        departement = data.get("departement")
        profit = data.get("profit")

        Sale.objects.create(
            departement=Departement.objects.get(zip_code=str(departement)),
            profit=profit,
        )

        message = {"message": "Sale successfully created!"}
        json.dumps(message, indent=4)
        return JsonResponse(message, json_dumps_params={"indent": 4})


# DetailView for every model
class DepartementDetailView(DetailView):
    template_name = "departement_detail.html"
    model = Departement

    def render_to_response(self, context, **response_kwargs):
        data = {
            "id": self.object.id,
            "name": self.object.name,
            "zip_code": self.object.zip_code,
            "price_m2": self.object.price_m2,
            "meteo": self.object.meteo,
            "longitude": self.object.longitude,
            "latitude": self.object.latitude,
            "costs": self.object.costs(),
        }
        return JsonResponse(data)


class MachineDetailView(DetailView):
    template_name = "machine_detail.html"
    model = Machine

    def render_to_response(self, context, **response_kwargs):
        data = {
            "id": self.object.id,
            "name": self.object.name,
            "price": self.object.price,
        }
        return JsonResponse(data)


class FactoryDetailView(DetailView):
    template_name = "factory_detail.html"
    model = Factory

    def render_to_response(self, context, **response_kwargs):
        data = {
            "id": self.object.id,
            "name": self.object.name,
            "area": self.object.area,
            "departement_ID": self.object.departement.id,
            "machines_IDs": [machine.id for machine in self.object.machines.all()],
            "stocks_IDs": [stock.id for stock in self.object.stocks.all()],
            "recipes_IDs": [recipe.id for recipe in self.object.recipes.all()],
            "costs": str(self.object.costs()) + " €",
        }
        return JsonResponse(data)


class IngredientDetailView(DetailView):
    template_name = "ingredient_detail.html"
    model = Ingredient

    def render_to_response(self, context, **response_kwargs):
        data = {
            "id": self.object.id,
            "name": self.object.name,
        }
        return JsonResponse(data)


class IngredientQuantityDetailView(DetailView):
    template_name = "ingredientquantity_detail.html"
    model = IngredientQuantity

    def render_to_response(self, context, **response_kwargs):
        data = {
            "id": self.object.id,
            "ingredient_ID": self.object.ingredient.id,
            "quantity": self.object.quantity,
        }
        return JsonResponse(data)


@method_decorator(csrf_exempt, name="dispatch")
class IngredientQuantityUpdateView(UpdateView):
    model = IngredientQuantity

    def post(self, request, *args, **kwargs):
        data = json.loads(request.body)
        quantity = data.get("quantity")
        id = data.get("id")

        IngredientQuantity.objects.filter(id=id).update(quantity=quantity)

        message = {"message": "Stocks successfully updated!"}
        json.dumps(message, indent=4)
        return JsonResponse(message, json_dumps_params={"indent": 4})


class PriceDetailView(DetailView):
    template_name = "price_detail.html"
    model = Price

    def render_to_response(self, context, **response_kwargs):
        data = {
            "id": self.object.id,
            "departement_ID": self.object.departement_name.id,
            "ingredient_ID": self.object.ingredient.id,
            "price": self.object.price,
        }
        return JsonResponse(data)


class RecipeDetailView(DetailView):
    template_name = "recipe_detail.html"
    model = Recipe

    def render_to_response(self, context, **response_kwargs):
        data = {
            "id": self.object.id,
            "name": self.object.name,
            "action_ID": self.object.action.id,
        }
        return JsonResponse(data)


class ActionDetailView(DetailView):
    template_name = "action_detail.html"
    model = Action

    def render_to_response(self, context, **response_kwargs):
        data = {
            "id": self.object.id,
            "action": self.object.action,
            "command": self.object.command,
            "duration": self.object.duration,
            "machine_ID": self.object.machine.id,
            "ingredients_Quantity_IDs": [
                ingredient.id for ingredient in self.object.ingredient.all()
            ],
        }
        return JsonResponse(data)


def index(request):
    departements = Departement.objects.all()
    factories = Factory.objects.all()

    # It's an API call to retrieve temperature
    # for every departements related to a factory
    """
    weatherKey = os.environ.get("WEATHER_KEY")
    for factory in factories:
        zip_code = factory.departement.zip_code
        source = requests.get(
            "https://api.openweathermap.org/data/2.5/weather?zip="
            + zip_code
            + "000"
            + ",fr&appid="
            + weatherKey
            + "&units=metric"
        )

        if source.status_code == 404:
            Departement.objects.filter(zip_code=zip_code).update(meteo="Not Found!")
        else:
            source = source.json()
            Departement.objects.filter(zip_code=zip_code).update(
                meteo=str(source["main"]["temp"]) + " °C"
            )
    """

    # Import a csv file and color up the departements
    # in function of their price/m2 from yellow to red
    data_file = settings.BASE_DIR / "data" / "prices.csv"
    departementsPrices = pandas.read_csv(data_file)

    # Url to display regions or departements
    url = "https://france-geojson.gregoiredavid.fr/repo/departements.geojson"

    fr_departements = requests.get(url).json()
    found = False

    # Adding price/m2 and temperature to display a popup on every departements mouse-hover
    for i in range(len(fr_departements["features"])):
        name = fr_departements["features"][i]["properties"]["nom"]
        for departement in departements:
            if name == departement.name:
                fr_departements["features"][i]["properties"][
                    "€/m²"
                ] = departement.price_m2
                fr_departements["features"][i]["properties"][
                    "temperature"
                ] = departement.meteo
                found = True
                break

        if not found:
            fr_departements["features"][i]["properties"]["€/m²"] = "NaN"
            fr_departements["features"][i]["properties"]["temperature"] = "Not Found!"

        found = False

    m = folium.Map(location=[46.71109, 1.7191036], zoom_start=6)

    # Functions related to Folium map rendering
    popup = folium.GeoJsonPopup(
        fields=["nom", "€/m²", "temperature"],
        aliases=["Name", "Price/m²", "Temperature"],
        localize=True,
        labels=True,
        style="background-color: yellow;",
    )

    tooltip = folium.GeoJsonTooltip(
        fields=["nom", "€/m²", "temperature"],
        aliases=["Name:", "Price/m²:", "Temperature:"],
        localize=True,
        sticky=False,
        labels=True,
        style="""
        background-color: #F0EFEF;
        border: 2px solid black;
        border-radius: 3px;
        box-shadow: 3px;
    """,
        max_width=800,
    )

    folium.Choropleth(
        geo_data=fr_departements,
        data=departementsPrices,
        columns=["departement_name", "price"],
        key_on="feature.properties.nom",
        fill_color="YlOrRd",
        fill_opacity=0.7,
        line_opacity=0.2,
        legend_name="Price/m² (€)",
        highlight=True,
        nan_fill_color="purple",
        nan_fill_opacity=0.4,
    ).add_to(m)

    folium.GeoJson(
        fr_departements,
        zoom_on_click=True,
        style_function=lambda feature: {
            "fillColor": "#00000000",
            "color": "black",
            "weight": 1,
            "dashArray": "5, 5",
        },
        tooltip=tooltip,
        popup=popup,
    ).add_to(m)

    # Calculating the total costs of every factory.
    # Displaying a marker in the map for every factory
    totalCosts = 0
    for factory in factories:
        # Reload the web browser page to buy new stocks
        factory.buyStocks()
        folium.Marker(
            location=factory.getLongitudeLatitude(),
            icon=folium.Icon(color="green", prefix="fa", icon="star"),
        ).add_to(m)
        totalCosts += factory.costs()

    context = {"map": m._repr_html_(), "totalCosts": str(totalCosts) + " €"}
    return render(request, "index.html", context)
