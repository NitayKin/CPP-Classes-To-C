typedef int (*get_limbs)(struct animal*);
typedef void (*eat)();

/*parent class*/
typedef struct{
	get_limbs get_limbs; /*virtual*/
	eat eat; /*non virtual*/
} animal;

/*child class*/
typedef struct{
	animal animal; /* have to be at the start of the struct!!! - because we implicitly convert pointers when calling functions*/
	int legs, hands;
} human;

/*another child class*/
typedef struct{
	animal animal; /* have to be at the start of the struct!!! - because we implicitly convert pointers when calling functions*/
	int legs;
} spider;

/*virtual function of animal (parent class) - returns the appropriate function for the class.*/
int animal_get_limbs(const animal *animal)
{
	return animal->get_limbs(animal);
}

/* non virtual function of animal (parent class) - */
void animal_eat(const animal *animal)
{
	printf("animal eats...\n");
	/* we can see, in difference with the virtaul function, we do have another "indirection" - we do the same for every object*/
}

/* get limbs function for human(child class)*/
int human_get_limbs(const animal *animal)
{
	human *my_human = (human*)animal;
	return (my_human->hands+my_human->legs);
}

/* get limbs function for spider(child class)*/
int spider_get_limbs(const animal *animal)
{
	spider *my_spider = (spider*)animal;
	return (my_spider->legs);
}

/* constructor for human*/
void new_human(human* human,int legs, int hands)
{
	human->hands=hands;
	human->legs = legs;
	human->animal.get_limbs = human_get_limbs;
	human->animal.eat=animal_eat;
}

/* constructor for spider*/
void new_spider(spider* spider,int legs)
{
	spider->legs = legs;
	spider->animal.get_limbs = spider_get_limbs;
	spider->animal.eat=animal_eat;
}


/* example of usage*/
void main()
{
	spider my_spider; /* objects will be on stack, could also use malloc - but then had to implement a destructor too(in this case not important becuase classes have no pointer variables)*/
	human my_human;
	new_human(&my_human, 2, 2);
	new_spider(&my_spider, 8);
	printf("human limbs : %d, spider limbs :%d\n",animal_get_limbs(&my_human) , animal_get_limbs(&my_spider)); /* difference results - virtual function*/
	animal_eat(&my_human); /* non virtual function*/
	animal_eat(&my_spider); /* non virtual function*/
}
