# Generated by Django 4.2.5 on 2023-10-04 06:55

from django.db import migrations


class Migration(migrations.Migration):
    dependencies = [
        ("foliumApp", "0014_vente"),
    ]

    operations = [
        migrations.RenameModel(
            old_name="Vente",
            new_name="Sale",
        ),
    ]