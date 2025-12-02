# Philo

**Philo** est un projet de l'école **42** visant à simuler le **problème des philosophes** (Dining Philosophers) en **C**, en utilisant les notions de **threads**, **mutex** et **gestion de la concurrence**.  
Le projet permet de comprendre les problèmes classiques de **synchronisation**, de **deadlock** et de **gestion des ressources partagées**.

## Objectifs

- Implémenter un simulateur de philosophes qui mangent, dorment et pensent.  
- Gérer correctement la synchronisation des forks pour éviter les **deadlocks** et **race conditions**.  
- Utiliser des threads (`pthread`) et des mutex pour contrôler l’accès aux ressources partagées.  
- Respecter les contraintes de temps (time to eat, time to sleep, time to die).  

## Usage

```bash
make
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_meals]
```
- number_of_philosophers : nombre de philosophes et de forks
- time_to_die : temps (en ms) avant qu’un philosophe meure sans manger
- time_to_eat : temps (en ms) pour manger
- time_to_sleep : temps (en ms) pour dormir
- [number_of_meals] : optionnel, nombre de fois que chaque philosophe doit manger

Exemple :
```bash
./philo 5 800 200 200
./philo 4 410 200 200 7
```
Fonctionnalités

- Gestion des threads pour chaque philosophe
- Synchronisation avec mutex pour les forks
- Affichage en temps réel des actions des philosophes
- Respect des contraintes de temps pour chaque action
