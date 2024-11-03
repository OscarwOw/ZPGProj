P�ep�n�n� sc�n za b�hu: Ano 
	ovl�danie pomocou triedy InputManager klavesova skratka n //v backlogu task na zmenu klavesy
	o zmenu sceny sa stara singleton trieda SceneManager konkr�tne funkcia SwitchScene(sceneName)
		sceneName dostaneme z funkcie getNextScene() ktor� vr�ti n�zov nasleduj�cej sceny // umoznujem nazyvat sceny stringami s napadom �e si u�ivate� bude m�c� vytvori� vlastn� s vlastn�m n�zvom.

a) Z�kladn� sc�na: Ano
	o tvorbu sceny sa stara singleton trieda SceneGenerator o z�kladn� scenu funkcia generateDefaultScene()

b) Sc�na s lesem: Ano
	funkcia generateForestScene() //aktualne nevyrie�en� bug s kermi ktor� sa ob�as zle vykreslia

c) Sc�na se �ty�mi kuli�kami: Ano
	funkcia generateSphereScene()

d) Sc�na pro demonstraci pou�it� v�ech shader� (Konstantn�, Lambert, Phong a Blinn): Ano
	funkcia generateShadersSphereScene()

Sv�tlo: Ano 
	svetlo aktu�lne vytv�ra trieda LightSource ktor� ded� z drawable object // poz�cia + viditeln� objekt
	svetlo funguje na design paterne observer. vytvoren� interface ILightObserver
	pri ka�dom vykreslen� sa nahraj� do shaderu data vo funkci� updateTransformation()

Z�kladn� t��dy (ShaderProgram, DrowableObject, Camera, Controller): Ano
	Controller nazvan� InputManager
	pipelina k vykresleniu je SceneManager::getCurrentScene()->Scene::draw()->foreach(DrawableObjects.Draw)->shaderProgram.use()->draw
	modely s� ne�ikovne v drawableObject //v backlogu upravi� na model
	shadery s� v samostatn�ch tex��koch
	transform�cie s� vo funkci�ch translate, scale, rotate ktor� ulo�ia transform�ciu do premennej a t� sa nesk�r pri vykreslen� pou�ije // backlog samostatn� triedy rozpracovan�


Transformace (Composite pattern): ne 
	rozpracovan� v suboroch TransformationScale, TransformationTranslate, TransformationRotate, Transformation, TransformationComposite
	je potreba dotiahn��
	inak tranform�cie norm�lne funguj�

Z�klady OOP

a) Encapsulation (zapouzd�en�): Ano
	takmer v�etky triedy pou��vaj� getre a setre.

b) Inheritance (d�di�nost) Ano
	napr�klad LightSource ded� z DrawableObject alebo Interfaci pri ILightObserver alebo ICameraObserver je ich aj viac.

c) Polymorphism (polymorfismus neboli mnohotv�rnost): Ano
	setViewMatrix() override; a �al�ie

Vertex a fragment shadery pros�m ulo�te do textov�ch souboru a pou�ijte p�ilo�en� ShaderLoader pro jejich na��t�n�: Ano
	samostatn� subory: vert_blinn.shader, frag_blinn.shader, vert_phong.shader, frag_phong.shader
	na��tava ShaderLoader.