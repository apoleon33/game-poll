#define nombreBoutons 4
#define nombreIRLeds 4

const int pinBoutons[nombreBoutons] = {2, 3, 4, 5};
const int pinIRLeds[nombreIRLeds] = {8, 9, 10, 11};
const int pinIRCapteurs[nombreIRLeds] = {14, 15, 16, 17}; // autant de capteurs que de leds mdr logique
const int pinLedVerte = 6;
const int pinLedRouge = 7;

const int seuil = 100; // seuil à partir duquel une carte est détectée
bool BoutonPresse = false;

int caractereAEnvoyer = 1; // le numéro de la réponse

String questionnaireReference = "JPO-Fev-2022"; // à envoyer quand on connecte l'arduino
int numeroCarte = 0;

void setup()
{
    for (int i = 0; i < nombreIRLeds; i++)
    {
        pinMode(pinBoutons[i], INPUT);
        pinMode(pinIRLeds[i], OUTPUT);
        pinMode(pinIRCapteurs[i], INPUT);
    }
    pinMode(pinLedVerte, OUTPUT);
    pinMode(pinLedRouge, OUTPUT);

    // on allume les leds infrarouges
    for (int i = 0; i < nombreIRLeds; i++)
    {
        digitalWrite(pinIRLeds[i], HIGH);
    }

    Serial.begin(115200);
    Serial.println(questionnaireReference);
}

void loop()
{
    while (numeroCarte == 0)
    {
        /* détection  de la carte entrée*/
        numeroCarte = 0;
        for (int i = 0; i < nombreIRLeds; i++)
        { /*on calcule la somme binaire des trous en la convertissant en décimal */

            int value = analogRead(pinIRCapteurs[i]);
            numeroCarte += (value > seuil) ? pow(2, i) : 0;
            /* la ligne dessus équivaut à ca enft
            if (value > seuil)
            {
                numeroCarte += pow(2,i);
            } else{
                numeroCarte += 0;
            } */
        }
        delay(1000;)
    }

    /* détection du bouton cliqué */
    bool BoutonPresse = false;
    while (BoutonPresse == false)
    { /* tant que 1 bouton n'est pas pressé on ne sort pas de cette boucle*/
        for (int i = 0; i < nombreBoutons; i++)
        {
            int valeurBouton = digitalRead(pinBoutons[i]);
            if (valeurBouton == 1)
            {
                caractereAEnvoyer = i;
                BoutonPresse = true; // un bouton a été pressé, on sort de la boucle
            }
        }
    }

    /* envoie des données à l'ordinateur
    Le big brain move:
    on additionne '@' ( caractère ascii n°64) au numero de la question convertit en décimal,
    Ainsi si c'est la question B, ca va faire 64 + 2 = 66 égale au caractère ascii 'B'
    */
    Serial.print((char)('@' + (numeroCarte + 1)));
    Serial.println(caractereAEnvoyer);

    /* on attend que la carte soit sortit de son boîtier*/
    while (numeroCarte != 0)
    { /* détection  de la carte entrée*/
        numeroCarte = 0;
        for (int i = 0; i < nombreIRLeds; i++)
        { /*on calcule la somme binaire des trous en la convertissant en décimal */

            int value = analogRead(pinIRCapteurs[i]);
            numeroCarte += (value > seuil) ? pow(2, i) : 0;
            /* la ligne dessus équivaut à ca enft
            if (value > seuil)
            {
                numeroCarte += pow(2,i);
            } else{
                numeroCarte += 0;
            } */
        }
    }

    numeroCarte = 0;
}