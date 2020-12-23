#ifndef MODEL_H
#define MODEL_H

class Model {

public:

    // For Singleton
    static Model& get_instance();

    // disallow copy/move construction or assignment
    Model(Model& obj) = delete;
    Model(Model&& obj) = delete;
    Model& operator= (Model& obj) = delete;
    Model& operator= (Model&& obj) = delete;

private:
    // create the initial objects
    Model();
    ~Model(){}

};

#endif