# Generated by Django 4.2.5 on 2023-09-28 13:23

from django.db import migrations


class Migration(migrations.Migration):
    dependencies = [
        ("foliumApp", "0008_action_ingredient_machine_recipe_price_and_more"),
    ]

    operations = [
        migrations.RenameField(
            model_name="departement",
            old_name="departement_name",
            new_name="name",
        ),
    ]