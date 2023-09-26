from django.shortcuts import render
import folium
import random
import requests
import pandas
from django.conf import settings
from .models import Departement

no_of_colors=100
colors=["#"+''.join([random.choice('0123456789ABCDEF') for i in range(6)])
       for j in range(no_of_colors)]
# print(colors)

"""
    //Régions
    https://france-geojson.gregoiredavid.fr/repo/regions.geojson

    //Départements
    https://france-geojson.gregoiredavid.fr/repo/departements.geojson

"""

def index(request):
    prices = Departement.objects.all()
    
    for price in prices:
        zip_code = price.zip_code
        source = requests.get('https://api.openweathermap.org/data/2.5/weather?zip='
                               + zip_code + '000' + ',fr&appid=cc37ea913904c8044ba2b814464bcfee&units=metric')
        
        if source.status_code == 404: 
            Departement.objects.filter(zip_code = zip_code).update(meteo = 'Not Found!')
        else:
            source = source.json()
            Departement.objects.filter(zip_code = zip_code).update(meteo = str(source['main']['temp']) + ' °C')
    
    
    
    
    data_file = settings.BASE_DIR / 'data' / 'prices.csv'
    departements = pandas.read_csv(data_file)
    print(departements)
    url = "https://france-geojson.gregoiredavid.fr/repo/departements.geojson"

    
    fr_departements = requests.get(url).json()
    found = False

    for i in range(len(fr_departements['features'])):
        name = fr_departements['features'][i]['properties']['nom']
        for price in prices:

            if name == price.departement_name:
                fr_departements['features'][i]['properties']['€/m²'] = price.price_m2
                fr_departements['features'][i]['properties']['temperature'] = price.meteo
                found = True
                break

        if not found:
            fr_departements['features'][i]['properties']['€/m²'] = 'NaN'
            fr_departements['features'][i]['properties']['temperature'] = 'Not Found!'

        found = False

    m = folium.Map(location=[46.71109, 1.7191036], zoom_start=6)


    
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
    data=departements,
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

    folium.GeoJson(fr_departements, zoom_on_click=True,
    style_function=lambda feature: {
        "fillColor": '#00000000', 
        'color': 'black',
        "weight": 1,
        "dashArray": "5, 5",
    },
    tooltip=tooltip,
    popup=popup,
    ).add_to(m)

    context = {'map': m._repr_html_()}
    return render(request, 'index.html', context)
