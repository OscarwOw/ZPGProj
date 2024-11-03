Pøepínání scén za bìhu: Ano 
	ovládanie pomocou triedy InputManager klavesova skratka n //v backlogu task na zmenu klavesy
	o zmenu sceny sa stara singleton trieda SceneManager konkrétne funkcia SwitchScene(sceneName)
		sceneName dostaneme z funkcie getNextScene() ktorá vráti názov nasledujúcej sceny // umoznujem nazyvat sceny stringami s napadom e si uivate¾ bude môc vytvori vlastnú s vlastnım názvom.

a) Základní scéna: Ano
	o tvorbu sceny sa stara singleton trieda SceneGenerator o základnú scenu funkcia generateDefaultScene()

b) Scéna s lesem: Ano
	funkcia generateForestScene() //aktualne nevyriešenı bug s kermi ktoré sa obèas zle vykreslia

c) Scéna se ètyømi kulièkami: Ano
	funkcia generateSphereScene()

d) Scéna pro demonstraci pouití všech shaderù (Konstantní, Lambert, Phong a Blinn): Ano
	funkcia generateShadersSphereScene()

Svìtlo: Ano 
	svetlo aktuálne vytvára trieda LightSource ktorá dedí z drawable object // pozícia + viditelnı objekt
	svetlo funguje na design paterne observer. vytvorenı interface ILightObserver
	pri kadom vykreslení sa nahrajú do shaderu data vo funkcií updateTransformation()

Základní tøídy (ShaderProgram, DrowableObject, Camera, Controller): Ano
	Controller nazvanı InputManager
	pipelina k vykresleniu je SceneManager::getCurrentScene()->Scene::draw()->foreach(DrawableObjects.Draw)->shaderProgram.use()->draw
	modely sú nešikovne v drawableObject //v backlogu upravi na model
	shadery sú v samostatnıch texákoch
	transformácie sú vo funkciách translate, scale, rotate ktoré uloia transformáciu do premennej a tá sa neskôr pri vykreslení pouije // backlog samostatné triedy rozpracované


Transformace (Composite pattern): ne 
	rozpracovanı v suboroch TransformationScale, TransformationTranslate, TransformationRotate, Transformation, TransformationComposite
	je potreba dotiahnú
	inak tranformácie normálne fungujú

Základy OOP

a) Encapsulation (zapouzdøení): Ano
	takmer všetky triedy pouívajú getre a setre.

b) Inheritance (dìdiènost) Ano
	napríklad LightSource dedí z DrawableObject alebo Interfaci pri ILightObserver alebo ICameraObserver je ich aj viac.

c) Polymorphism (polymorfismus neboli mnohotvárnost): Ano
	setViewMatrix() override; a ïalšie

Vertex a fragment shadery prosím ulote do textovıch souboru a pouijte pøiloenı ShaderLoader pro jejich naèítání: Ano
	samostatné subory: vert_blinn.shader, frag_blinn.shader, vert_phong.shader, frag_phong.shader
	naèítava ShaderLoader.