# Vumetru 
## Scurta descriere

In cadrul acestui proiect am dezvoltat un sistem ce contine 3 tipuri de filtre care sa separe sunetul receptat in functie de frecventa acestuia:
- Filtru Trece Jos pentru frecvente joase
- Filtru Trece Baza pentru frecvente medii
- Filtru Trece Sus pentru frecvente inalte

Pe langa acestea, folosim un microfon analogic, un microcontroller esp32-wroom-32 si o matrice de leduri pentru a afisa valorile.

## Modelul de functionalitate

### Receptarea si procesarea sunetului

O data ce sunetul este receptat de catre microfon si filtrat prin acest set, valorile de intensitate de sunet pentru fiecare categorie de frecvente sunt transmise catre microcontroller.

```
Baga ss cu exemplu de valori
```

