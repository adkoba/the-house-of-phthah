J'ai vu Thibault Jeudi dernier qui m'a fait une rapide présentation du projet. Pour l'instant j'ai juste téléchargé le code source et je me suis occupé de le faire tourner. Je découvre encore le code que vous avez fait et le fonctionnement général de Ogre (via les tutoriaux). Du coup la conversation avec Thibault a bcp plus porté sur le thème que vous vous étiez fixé. Si j'ai ben compris le but est de faire un FPS avec comme trame de fond l'Égypte et le dieu phthat (si j'ai bien compris c'est le dieu de la mort dans la mythologie égyptienne tardive ??, idéal pour un FPS :)). Bref pour l'instant notre conversation à plus portée sur des éléments du jeu.
  1. Possibilité d'ajouter un temple (utilisation dans un premier tps d'un bsp quake), je te suggère de regarder l'exemple "Quake3 level loading" de Ogre.
    * ça nécessitera la détection de collision
    * l'utilisation d'un scene manager spécifique
  1. Ajout d'un personnage et d'ennemis sur qui il pourra tirer. Encore faut-il définir ce qu'il va tirer (armes,....). Pour les adversaires, on envisageait dans un premier temps d'utiliser des cylindres (mais bon en fait on peut très bien utiliser les fichiers robot.mesh ou ninja.mesh pas très en rapport mais plus sexy)
    * nécessitera de l'IA
    * détection de collisions
    * la mise en place d'une structure objet pour gérer les persos.
    * Ajout d'input pour diriger le joueur
    * .....

Et je dois en oublier. J'ai proposé à Thibault de réfléchir sur l'architecture générale du jeu et de produire des schémas UML du code déjà fait. Je pencherais bien aussi sur l'ajout de personnages (non-animé pour l'instant) et sur les interactions entre eux. Et pour finir, je me propose aussi dans la mesure du possible d'assurer le support du code sous Linux. Thibault de son coté proposé de travailler sur tout ce qui est shader et qualité du rendu.

Voilà, je sais pas trop ou tu en es toi, quels sont tes idées, et tes envies... mais bon je suppose que tu n'en manques pas.