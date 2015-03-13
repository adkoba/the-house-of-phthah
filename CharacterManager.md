# Introduction #

Bon alors après avoir été un élève studieux et avoir lu quasiment tous les tutoriaux de Ogre, je me lance enfin sur le projet. Dans les tâches que je me suis assigné pour l’instant, il y a juste :
  1. Établir un diagramme de classes du projet en l'état actuel
  1. Ajouter un gestionnaire de personnage

# Diagramme de classes #

Pour le premier point, je n’ai pas encore arrêté de choix sur un modeleur UML, je vais essayer d’en trouver un gratuit, assez souple vis-à-vis de la norme, qui proposent les diagrammes de base (use case, séquence, classes), et qui peut faire de l’export en image, voir mieux en svg (pour un futur site web).

# Gestionnaire de personnages #

Pour le deuxième point, mon travail va se faire en trois étapes :

  1. Ajouter un gestionnaire de personnages qui aura pour l’instant que deux buts :
    * ajouter des personnages sur l’ile,
    * permettre le chargement des personnages à partir d’un fichier de conf

  1. Ajouter deux types de personnages :

  * Le joueur
    * Il sera manipulable via la souris pour son orientation et via le clavier pour sa direction
    * Il aura une caméra attaché à lui avec la possibilité de passer en vue 1<sup>ier</sup>Personne ou 3<sup>ième</sup>Personne
    * Ses animations seront idle, walk (peut-être courir suivant ce que ça donne), et tirer

  * Les ennemis qui seront fixe dans cette première version.

--> A cette étape, commenceront à se poser des pbm de physiques :
  * Détection de collisions entre personnages, du tir sur vers un ennemi
  * Détection lors du déplacement du joueurs des zones de terrain inaccessible (pente trop raide par exemple, eau…)

  1. Implémenter un comportement de base pour les ennemis (juste le déplacement)

--> A cette étape, il faudra réfléchir sérieusement à l’implémentation d’un moteur d’IA incluant pathfinding, aide à la décision....

# Un mot sur l'architecture #

L’architecture proposée devra permettre :
  1. de pouvoir ajouter facilement de nouveau types de personnages :
    * partie en réseau : donc soit des amis, soit des ennemis
    * civil qui n’ont rien avoir dans la tuerie
    * …..
  1. de pouvoir décorréler l’IA et les entités qui l’utiliseront
  1. d'ajouter facilement des comportements (représenté par des animations) aux personnages

Pour l’instant, je vais utiliser comme personnage le robot fournit par ogre. C’est loin d’être ce que l’on aimerait au final, mais il a l’avantage de proposer toutes les anim dont on a besoin et puis ça fera plus joli quand même qu'un cylindre.

# Quelques idées sur le reste #

Voili, voilà sommairement ce que j’ai prévu. L’idée est de pouvoir rapidement disposer d’une map jouable. J’ai pensé que d’autres éléments pouvaient-être étudiés en parallèle :

  * Ajout d’un bâtiment au centre de la map actuelle. Le plus simple serait d’utiliser le bsp de quake fournit, mais de le mettre soit dans une colline proéminente au centre de la map, soit dans une sorte de très grande pyramide (modèle 3D assez facile à produite).
    * Il faudrait étudier plus en avant le changement de ……

  * Ajout d’éléments statique dans le décor de la map (rocher, arbre….)
    * Y a un tutoriel avancé de Ogre qui parle de ce style d’objet

  * Peaufiner le rendu de l’eau
    * Quelle s’étende à perte de vue autour de l’île
    * Rendre l’eau plus interactive

Bref si on rajoute vos idées, il y a de quoi faire.

A et pour finir j’essaierais de maintenir dans ce post, l’état d’avancement du travail, et les solutions utilisés pour chaque pbm, manière que vous puissiez facilement suivre, réagir, donner des idées….