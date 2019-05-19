#include <vector>
#include <memory>
#include <algorithm>
#include <random>
#include <iostream>

#include "models/player.hpp"
#include "models/digit.hpp"
#include "models/sea.hpp"
#include "models/meter.hpp"

#include "models/arrow.hpp"
#include "models/carrier.hpp"

#include "models/destroyer.hpp"
#include "models/destroyerE.hpp"
#include "models/island.hpp"
#include "models/volcano.hpp"
#include "models/gasoline.hpp"
#include "models/ring.hpp"
#include "models/missile.hpp"
#include "models/bomb.hpp"
#include "models/cannon.hpp"
#include "models/parachute.hpp"

float zoom = 1.0f;

static std::unique_ptr<Player> player;

static std::shared_ptr<Meter> speed_meter;
static std::shared_ptr<Meter> altitude_meter;
static std::shared_ptr<Meter> fuel_meter;

/* arrow */
static std::shared_ptr<Arrow> arrow;

/* friendly forces */
static std::shared_ptr<Carrier> carrier;
static std::array<std::shared_ptr<Destroyer>, 3> destroyersF;
static std::array<std::shared_ptr<DestroyerE>, 3> destroyersE;

/* level */
static std::array<std::shared_ptr<Island>, 3> islands;
static std::array<std::shared_ptr<Volcano>, 3> volcanos;

/* collectables */
static std::array<std::shared_ptr<Gasoline>, 3> gasolines;
static std::array<std::shared_ptr<Ring>, 3> rings;

/* weaponary */
static std::array<std::shared_ptr<Missile>, 4> missiles;
static std::array<std::shared_ptr<Bomb>, 4> bombs;

/* enemy weaponary */
static std::array<std::shared_ptr<Cannon>, 24> cannons;
static std::array<std::shared_ptr<Parachute>, 24> enemies;

/* all models */
static std::vector<std::shared_ptr<IModel>> models;
static std::vector<std::shared_ptr<IModel>> fixed_models;

/* level properties */
enum class camera_modes {
    plane_view,
    top_view,
    tower_view,
    follow_cam,
    helicoptor_view
};

static struct {
    int tick;
    camera_modes camera_mode;
} level;

void atexit_handler() {
    std::cout << "Score: " << player->get_score() << std::endl;
}

void initLevel() {
    assert(std::atexit(atexit_handler) == 0);

    level.tick = 0;
    level.camera_mode = camera_modes::follow_cam;
  
    player = std::make_unique<Player>();
    player->set_position(glm::vec3(3000.0, 50.0, 3000.0f));

    speed_meter = std::make_shared<Meter>();
    altitude_meter = std::make_shared<Meter>();
    fuel_meter = std::make_shared<Meter>();

    fixed_models.emplace_back(std::dynamic_pointer_cast<IModel, Meter>(speed_meter));
    speed_meter->set_offset(glm::vec3(-10.0f, -4.0f, 0.0f));
    fixed_models.emplace_back(std::dynamic_pointer_cast<IModel, Meter>(altitude_meter));
    altitude_meter->set_offset(glm::vec3(-12.0f, -4.0f, 0.0f));

    fixed_models.emplace_back(std::dynamic_pointer_cast<IModel, Meter>(fuel_meter));
    fuel_meter->set_offset(glm::vec3(10.0f, -4.0f, 0.0f));

    models.emplace_back(new Sea());

    carrier = std::make_shared<Carrier>();
    models.emplace_back(carrier);

    for(auto& d : destroyersF) {
        d = std::make_shared<Destroyer>();
        models.emplace_back(d);   
    }

    carrier->set_position(glm::vec3(3000.0f, 50.0f, 3000.0f));
    destroyersF[0]->set_position(glm::vec3(3000.0f, 0.0f, 2500.0f));
    destroyersF[1]->set_position(glm::vec3(3000.0f, 0.0f, 3500.0f));
    destroyersF[2]->set_position(glm::vec3(2000.0f, 0.0f, 3000.0f));

    for(auto& i : islands) {
        i = std::make_shared<Island>();
        models.emplace_back(i);   
    }
    islands[0]->set_position(glm::vec3(150.0f, 0.0f, 500.0f));
    islands[1]->set_position(glm::vec3(0.0f, 0.0f, 1000.0f));
    islands[2]->set_position(glm::vec3(100.0f, 0.0f, -100.0f));

    arrow = std::make_shared<Arrow>();
    arrow->set_position(glm::vec3(150.0, 200.0, 500.0));
    arrow->set_rotation(glm::vec3(180.0f, 0.0f, 0.0f));
    models.emplace_back(arrow);

    for(auto& v : volcanos) {
        v = std::make_shared<Volcano>();
        models.emplace_back(v);   
    }
    volcanos[0]->set_position(glm::vec3(1500.0f, 0.0f, 500.0f));
    volcanos[1]->set_position(glm::vec3(500.0f, 0.0f, 1000.0f));
    volcanos[2]->set_position(glm::vec3(1500.0f, 0.0f, -100.0f));

    for(auto& g : gasolines) {
        g = std::make_shared<Gasoline>();
        models.emplace_back(g);   
    }
    gasolines[0]->set_position(glm::vec3(2500.0f, 100.0f, 500.0f));
    gasolines[1]->set_position(glm::vec3(-1500.0f, 100.0f, 1000.0f));
    gasolines[2]->set_position(glm::vec3(-1000.0f, 100.0f, -100.0f));

    for(auto& r : rings) {
        r = std::make_shared<Ring>();
        models.emplace_back(r);   
    }
    rings[0]->set_position(glm::vec3(-500.0f, 150.0f, 500.0f));
    rings[1]->set_position(glm::vec3(-250.0f, 100.0f, 100.0f));
    rings[2]->set_position(glm::vec3(-100.0f, 120.0f, -100.0f));

    for(auto& m : missiles) {
        m = std::make_shared<Missile>();
        m->disable();
        models.emplace_back(m);   
    }

    for(auto& b : bombs) {
        b = std::make_shared<Bomb>();
        b->disable();
        models.emplace_back(b);   
    }

    for(auto& m : cannons) {
        m = std::make_shared<Cannon>();
        m->disable();
        models.emplace_back(m);   
    }

    for(auto& e : enemies) {
        e = std::make_shared<Parachute>();
        e->disable();
        models.emplace_back(e);
    }
}

void levelDraw(GLFWwindow* window, glm::mat4 VP) {
    auto old_pos = player->get_position();
    auto old_rot = player->get_rotation();

    level.tick++;

    auto ispressed = [&window](int key) {
        return glfwGetKey(window, key) == GLFW_PRESS;
    };

    auto ispressedM = [&window](int key) {
        return glfwGetMouseButton(window, key) == GLFW_PRESS;
    };

    if(ispressed(GLFW_KEY_1))
        level.camera_mode = camera_modes::plane_view;
    if(ispressed(GLFW_KEY_2))
        level.camera_mode = camera_modes::top_view;
    if(ispressed(GLFW_KEY_3))
        level.camera_mode = camera_modes::tower_view;
    if(ispressed(GLFW_KEY_4))
        level.camera_mode = camera_modes::follow_cam;
    if(ispressed(GLFW_KEY_5))
        level.camera_mode = camera_modes::helicoptor_view;

    key_state_t keys;
    keys.W = ispressed(GLFW_KEY_W);
    keys.A = ispressed(GLFW_KEY_A);
    keys.S = ispressed(GLFW_KEY_S);    
    keys.D = ispressed(GLFW_KEY_D);
    keys.Q = ispressed(GLFW_KEY_Q);
    keys.E = ispressed(GLFW_KEY_E);
    keys.up = ispressed(GLFW_KEY_UP);
    keys.down = ispressed(GLFW_KEY_DOWN);
    keys.space = ispressed(GLFW_KEY_SPACE);
    keys.lshift = ispressed(GLFW_KEY_LEFT_SHIFT);
    keys.lctrl = ispressed(GLFW_KEY_LEFT_CONTROL);
    keys.lalt = ispressed(GLFW_KEY_LEFT_ALT);
    keys.lbutton = ispressedM(GLFW_MOUSE_BUTTON_LEFT);
    keys.rbutton = ispressedM(GLFW_MOUSE_BUTTON_RIGHT);

    player->input(keys);
    player->tick(models);

    if(level.tick%120 == 0)
        player->give_score(5);

    if((keys.lctrl || keys.lbutton) && level.tick%60 == 0) {
        /* fire missile */
        std::shared_ptr<Missile> free;
        for(auto& m : missiles) {
            if(!m->status()) {
                free = m;
                break;
            }
        }

        if(free) {
            /* fire missile */
            glm::vec4 local_fv = glm::vec4(0.0, 0.0, -1.0, 0.0);
            glm::vec3 rotation = player->get_rotation().local;
            rotation += player->get_rotation().global;

            glm::mat4 R(1);
            R *= glm::rotate(glm::radians(rotation.y), glm::vec3(0, 1, 0));
            R *= glm::rotate(glm::radians(rotation.z), glm::vec3(0, 0, 1));
            R *= glm::rotate(glm::radians(rotation.x), glm::vec3(1, 0, 0));

            glm::vec3 global_fv = glm::normalize(glm::vec3(R * local_fv));
            glm::vec3 target = player->get_position() + global_fv * 2500.0f;

            free->set(player->get_position(), target);
            free->set_rotation(rotation);
            free->enable();
        }
    }

    for(auto& m : missiles) {
        if(m->status()) {
            for(auto& e : enemies) {
                if(glm::length(m->get_position() - e->get_position()) < 10.0f) {
                    /* enemy dies */
                    e->disable();
                    m->disable();
                    break;
                }
            }

            for(auto& i : islands) {
                if(glm::length(m->get_position() - i->get_position()) < 50.0f) {
                    /* island skinks */
                    i->sink();
                    m->disable();
                    break;
                }
            }
        }
    }

    for(auto& b : bombs) {
        if(b->status()) {
            for(auto& e : enemies) {
                if(glm::length(b->get_position() - e->get_position()) < 10.0f) {
                    /* enemy dies */
                    e->disable();
                    b->disable();
                    break;
                }
            }

            for(auto& i : islands) {
                if(glm::length(b->get_position() - i->get_position()) < 50.0f) {
                    /* island skinks */
                    i->sink();
                    b->disable();
                    break;
                }
            }
        }
    }

    arrow->disable();
    for(auto& i : islands) {
        if(i->status()) {
            auto pos = i->get_position();
            pos.y = 200.0f;
            arrow->set_position(pos);
            arrow->enable();
            break;
        }
    }

    if(level.tick%240 == 0) {
        for(auto& i : islands) {
            if(glm::length(i->get_position() - player->get_position()) < 2500.0f) {
                /* launch SAM */
                for(auto& m : cannons) {
                    if(!m->status()) {     
                        m->set(i->get_position(), player->get_position());
                        m->enable();
                        break;
                    }
                }
            }
        }
    }

    if((keys.lshift || keys.rbutton) && level.tick%60 == 0) {
        /* drop bomb */
        std::shared_ptr<Bomb> free;
        for(auto& b : bombs) {
            if(!b->status()) {
                free = b;
                break;
            }
        }
        if(free) {
            /* drop bomb */
            glm::vec4 local_fv = glm::vec4(0.0, 0.0, -1.0, 0.0);
            glm::vec3 rotation = player->get_rotation().local;
            rotation += player->get_rotation().global;

            glm::mat4 R(1);
            R *= glm::rotate(glm::radians(rotation.y), glm::vec3(0, 1, 0));
            R *= glm::rotate(glm::radians(rotation.z), glm::vec3(0, 0, 1));
            R *= glm::rotate(glm::radians(rotation.x), glm::vec3(1, 0, 0));

            glm::vec3 target = player->get_position();
            target.y = 0.0f;

            free->set(player->get_position(), target);
            free->set_rotation(rotation);
            free->enable();
        }
    }

    if(level.tick%120 == 0) {
        for(auto& e : enemies) {
            if(!e->status()) {
                e->enable();
                e->set_position(glm::vec3(rand()/float(RAND_MAX) * 1000.0, rand()/float(RAND_MAX) * 1000.0, 100.0f + rand()/float(RAND_MAX) * 200.0));
                break;
            }
        }
    }

    for(auto& m : models) {
        if(m->is_dynamic()) {
            std::dynamic_pointer_cast<IDynamic, IModel>(m)->tick();
        }
    }
    
    for(auto& m : models)
        m->draw(VP);

    fuel_meter->set_value(player->get_fuel());
    altitude_meter->set_value(glm::clamp(player->get_position().y/1000.0f, 0.0f, 1.0f));
    speed_meter->set_value(glm::length(player->get_velocity().translational));

    if(player->get_position().y < 0.0 || player->get_fuel() < 0.0)
        std::exit(0);

    auto pr = player->get_rotation().global;
    glm::mat4 R = glm::rotate(glm::radians(pr.z), glm::vec3(0, 0, 1));
    R *= glm::rotate(glm::radians(pr.y), glm::vec3(0, 1, 0));
    R *= glm::rotate(glm::radians(pr.x), glm::vec3(1, 0, 0));
    for(auto& m : fixed_models) {
        auto offset = glm::vec4(std::dynamic_pointer_cast<Meter, IModel>(m)->get_offset(), 1.0f);
        offset = R * offset;
        m->set_position(player->get_position() + glm::vec3(offset));

        m->set_rotation(player->get_rotation().global);
        m->draw(VP);
    }

    player->draw(VP);
}

void get_camera(glm::vec3& eye, glm::vec3& target, glm::vec3& up) {
    switch(level.camera_mode) {
        case camera_modes::plane_view:
        {
            glm::vec4 local_fv = glm::vec4(0.0, 0.0, -10.0, 0.0);
            glm::mat4 R = glm::rotate(glm::radians(player->get_rotation().global.y), glm::vec3(0, 1, 0));
            glm::vec3 global_fv = glm::vec3(R * local_fv);

            eye = player->get_position() + global_fv;
            target = player->get_position() + global_fv * 2.0f;
            up = glm::vec3(0, 1, 0);
        }
        break;
        case camera_modes::top_view:
        {
            eye = player->get_position() + glm::vec3(0.0f, 200.0f, 0.0f);
            target = player->get_position();
            up = glm::vec3(0, 0, 1); 
        }
        break;
        case camera_modes::tower_view:
        {
            eye = glm::vec3(3000.0f, 100.0f, 3000.0f);
            target = player->get_position();
            up = glm::vec3(0, 1, 0); 
        }
        break;
        case camera_modes::follow_cam:
        {
            glm::vec4 local_fv = glm::vec4(0.0, 0.0, -1.0, 0.0);
            glm::mat4 R = glm::rotate(glm::radians(player->get_rotation().global.y), glm::vec3(0, 1, 0));
        
            glm::vec3 global_fv = glm::vec3(R * local_fv);

            eye = player->get_position() - global_fv * 30.0f + glm::vec3(0.0, 10.0, 0.0);
            target = player->get_position();
            up = glm::vec3(0, 1, 0);
        }
        break;
        case camera_modes::helicoptor_view:
        {
            static GLfloat angle_y = 30, angle_x = 30;
            double xpos, ypos;

            extern GLFWwindow *window;
            glfwGetCursorPos(window, &xpos, &ypos);

            if(xpos < 300) {
                angle_y = std::min(angle_y + 1.0f, 135.0f);
            } else if(xpos > 1140) {
                angle_y = std::max(angle_y - 1.0f, -135.0f);
            }

            if(ypos < 200) {
                angle_x = std::min(angle_x + 1.0f, 135.0f);
            } else if(ypos > 700) {
                angle_x = std::max(angle_x + 1.0f, -135.0f);
            }

            std::cout << xpos << " " << ypos << std::endl;

            glm::vec4 local_fv = glm::vec4(0.0, 0.0, -1.0, 0.0);
            glm::mat4 R(1);
            R *= glm::rotate(glm::radians(angle_y), glm::vec3(0, 1, 0));
            R *= glm::rotate(glm::radians(angle_x), glm::vec3(1, 0, 0));

            glm::vec3 global_fv = glm::vec3(R * local_fv);

            eye = player->get_position() - global_fv * 30.0f * zoom + glm::vec3(0.0, 10.0, 0.0);
            target = player->get_position();
            up = glm::vec3(0, 1, 0);
        }
        break;
    }    
}