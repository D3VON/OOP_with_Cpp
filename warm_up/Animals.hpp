#ifndef ANIMALS_HPP
#define ANIMALS_HPP



struct Animal {
    // These are the public members that are
    // part of the public API.
    const char *type_name;
    int number_of_legs;
    void (*talk)(Animal *);
    void (*delet)(Animal *);
    // You may of course have your own private
    // members here.
    // ...
};

struct Dog {
    Animal animal;
    const char *name;
    int dog_tag_number;
    void (*fetch)(Dog *);
};

struct Poodle {
    Dog dog;
    const char *groomer;
    void (*primp)(Poodle *);
};

struct Fish {
    Animal animal;
    void (*swim)(Fish *);
};

Dog *Dog_new(const char *name, int tag);
Dog *Animal_downcast_Dog(Animal *a);

Poodle *Poodle_new(const char *name, int tag, const char *groomer);
Poodle *Animal_downcast_Poodle(Animal *);
Poodle *Dog_downcast_Poodle(Dog *);

Fish *Fish_new();
Fish *Animal_downcast_Fish(Animal *a);



#endif
