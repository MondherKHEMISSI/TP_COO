# Generated by Django 4.2.5 on 2023-09-29 21:39

from django.db import migrations


class Migration(migrations.Migration):
    dependencies = [
        ("foliumApp", "0010_departement_langitude_departement_latitude"),
    ]

    operations = [
        migrations.RenameField(
            model_name="departement",
            old_name="langitude",
            new_name="longitude",
        ),
    ]
