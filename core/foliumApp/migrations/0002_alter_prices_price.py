# Generated by Django 4.2.5 on 2023-09-25 22:05

from django.db import migrations, models


class Migration(migrations.Migration):
    dependencies = [
        ("foliumApp", "0001_initial"),
    ]

    operations = [
        migrations.AlterField(
            model_name="prices",
            name="price",
            field=models.IntegerField(),
        ),
    ]
