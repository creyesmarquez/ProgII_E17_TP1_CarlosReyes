#include "Ball.h"

std::vector<Ball* const> Ball::balls;

Ball::Ball()
: Sprite("Kirby.png", (int)x, (int)y, (int)BALL_RADIUS * 2, (int)BALL_RADIUS * 2)
, x(STARTING_X - BALL_RADIUS)
, y(STARTING_Y)
, dx(0.0f)
, dy(5.0f)
{
	onPlay = false;
	applyGravity = false;
}

Ball::Ball(float posX, float posY, Basket* platform)
: Sprite("Kirby.png", (int)x, (int)y, (int)BALL_RADIUS * 2, (int)BALL_RADIUS * 2)
, lifeX(posX)
, lifeY(posY)
, x(posX)
, y(posY)
, dx(0)
, dy(0)
{
	this->platform = platform;
	onPlay = false;
	applyGravity = false;

	//Place le nouvel obstacle créé dans un vecteur
	balls.push_back(this);
}

void Ball::Update(float dt)
{
	
	CheckCollision();

	//Inversion de la vitesse en x si la balle atteint un des côtés de la fenêtre
	if (x < 0)
	{
		dx = -dx;
		x = BALL_RADIUS;
	}

	if (x >(1000 - BALL_RADIUS * 2))
	{
		dx = -dx;
		x = 1000 - BALL_RADIUS * 2;
	}

	if (applyGravity)
	{
		//Modification de la vitesse selon l'accélération gravitationelle et le dt
		dy += GRAVITY * dt;
	}
	
	if (y > 900)
	{
		onPlay = false;
	}
	

	//Modication de la position en x selon la vitesse en x
	x += dx * dt;

	//Modication de la position en y selon la vitesse en y
	y += dy * dt;

	//Modification du destRect selon la nouvelle position de la balle
	SetPosition((int)x, (int)y);
}

void Ball::CheckCollision()
{
	for (int i = 0; i < Obstacle::GetObstaclesPtr()->size(); i++)
	{
		Obstacle* obstacle = Obstacle::GetObstaclesPtr()->at(i);

		if (GetCollider()->CollidesWith(static_cast<Circle*>(obstacle->GetCollider())) && !obstacle->GetIsDestroyed())
		{
			//Ajustement de la position de la balle pour quelle revienne au point réelle de collision
			AdjustPos(obstacle);
			
			Vector vectDir = Vector(dx, dy, 0);
			//Formation de la norme de la tangeante et normalisation
			Vector collisionNorm = Vector((x + BALL_RADIUS) - (obstacle->GetX() + OBSTACLE_RADIUS), (y + BALL_RADIUS) - (obstacle->GetY() + OBSTACLE_RADIUS), 0);
			collisionNorm.Normalize();
			//Réflexion du vecteur sur la tangeante
			Vector outVect = vectDir;
			float dotProduct = vectDir.Dot(&collisionNorm);
			collisionNorm.Scale(dotProduct * 2.0f);
			outVect.Substract(&collisionNorm);
			//Simulation de perte de vitesse lors de collision
			outVect.Scale(SPEED_REDUCTION);
			//Ajustement de la direction selon le rebond calculé
			dx = outVect.x;
			dy = outVect.y;
			//Détruit l'obstacle
			obstacle->Destroy();
			break;
		}
	}
}

void Ball::AdjustPos(Obstacle* obstacleCollided)
{
	//Vecteur de direction actuel
	Vector vectDir = Vector(dx, dy, 0);

	//Vecteur formé du centre de l'obstacle jusqu'au centre de la balle
	Vector ballObstacle = Vector((obstacleCollided->GetX() + OBSTACLE_RADIUS) - (x + BALL_RADIUS), (obstacleCollided->GetY() + OBSTACLE_RADIUS) - (y + BALL_RADIUS), 0);

	//Projection orthogonale du vecteur centres balle/obstacle sur le vecteur direction
	Vector centerDir = vectDir;
	centerDir.Scale(ballObstacle.Dot(&vectDir) / vectDir.Dot(&vectDir));

	//Distance réelle entre les deux centre si collision
	float realDist = BALL_RADIUS + OBSTACLE_RADIUS;

	//Longueur entre les centres balle/obstacle par rapport au vecteur direction
	float realDistCenterDir = sqrt(realDist * realDist + centerDir * centerDir - ballObstacle * ballObstacle);

	//Formation d'un vecteur avec la dernière donné
	Vector realCenterDir = vectDir;
	realCenterDir.Normalize();
	realCenterDir.Scale(-realDistCenterDir);

	//Formation d'un vecteur qui va du centre de la balle actuelle au centre de la balle au point de collision réelle
	Vector correction = realCenterDir;
	correction.Add(&centerDir);

	//Correction de la position selon le vecteur de correction
	x += correction.x;
	y += correction.y;
	SetPosition((int)x, (int)y);

	//Débuggage

	//std::cout << "Vect dir(" << vectDir.x << ", " << vectDir.y << ")" << " Length: " << vectDir.Length() << "; angle: " << vectDir.GetPolarAngleDeg() << std::endl;
	//std::cout << "Vect ballObstacle(" << ballObstacle.x << ", " << ballObstacle.y << ")" << ballObstacle.Length() << "; angle: " << ballObstacle.GetPolarAngleDeg() << std::endl;
	//std::cout << "Vect centerDir(" << centerDir.x << ", " << centerDir.y << ")" << centerDir.Length() << "; angle: " << centerDir.GetPolarAngleDeg() << std::endl;
	//std::cout << "Vect realCenterDir(" << realCenterDir.x << ", " << realCenterDir.y << ")" << realCenterDir.Length() << "; angle: " << realCenterDir.GetPolarAngleDeg() << std::endl;
	//std::cout << "Vect correction(" << correction.x << ", " << correction.y << ")" << correction.Length() << "; angle: " << correction.GetPolarAngleDeg() << std::endl;
	//std::cout << "realDist: " << realDist << std::endl;
	//std::cout << "realDistCenterDir: " << realDistCenterDir << std::endl;
	
	//std::cout << "Vérifié: " << realDist * realDist << " + " << centerDir * centerDir << " - " << ballObstacle * ballObstacle << std::endl;
}

Ball::~Ball()
{
	x, y, dx, dy = 0;
}