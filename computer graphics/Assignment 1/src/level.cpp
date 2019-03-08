#include <vector>
#include <memory>
#include <random>

#include "models/model.hpp"
#include "models/player.hpp"
#include "models/floor.hpp"
#include "models/wall.hpp"
#include "models/golden_coin.hpp"
#include "models/silver_coin.hpp"
#include "models/bronze_coin.hpp"
#include "models/magnet.hpp"
#include "models/treasure.hpp"
#include "models/life.hpp"
#include "models/fireline.hpp"
#include "models/firebeam.hpp"
#include "models/boomerang.hpp"
#include "models/digit.hpp"
#include "models/dragon.hpp"
#include "models/iceball.hpp"
#include "models/shield.hpp"
#include "models/waterball.hpp"

static std::unique_ptr<Player> player;
static std::shared_ptr<Magnet> magnet;
static std::shared_ptr<Boomerang> boomerang;
static std::shared_ptr<Dragon> dragon;
static std::shared_ptr<Iceball> iceball;
static std::shared_ptr<Shield> shield;
static std::shared_ptr<WaterBall> waterball;

int shield_tick = 0;
bool shield_given = false;

static std::vector<std::shared_ptr<Digit>> score_digits;
static std::shared_ptr<Digit> level_digit;
static std::shared_ptr<Digit> lives_digit;

/* all models */
static std::vector<std::shared_ptr<IModel>> models;

/* automatically moved with the level */
static std::vector<std::shared_ptr<IModel>> fixed_models;

/* level properties */
static struct {
    glm::vec3 position;
    glm::vec3 velocity;
    int tick;
} level;

glm::vec3 get_position() { return level.position; }

void initLevel() {
    level.position = glm::vec3(0.00f, 0.00f, 0.00f);
    level.velocity = glm::vec3(0.01f, 0.00f, 0.00f);
    level.tick = 0;

    /* create walls and floor */
    for(int i = 0; i < 25; i++) {
        float next;

        models.emplace_back(new Wall());
        next = (i * models.back()->get_size().x * models.back()->get_scale().x);
        models.back()->set_position(glm::vec3(next, 0.0, 0.0));

        models.emplace_back(new Floor());
        next = (i * models.back()->get_size().x * models.back()->get_scale().x);
        models.back()->set_position(glm::vec3(next, -3.5, 0.0));

        models.emplace_back(new Floor());
        next = (i * models.back()->get_size().x * models.back()->get_scale().x);
        models.back()->set_position(glm::vec3(next, 3.5, 0.0));
    }

    /* create special objects */
    {
        models.emplace_back(new Treasure());
        models.back()->set_position(glm::vec3(4.0f, 0.0f, 0.0f));

        models.emplace_back(new Life());
        models.back()->set_position(glm::vec3(10.0f, 0.0f, 0.0f));
    }

    /* create coins and enemies */
    std::mt19937 rng;
    std::uniform_real_distribution<> dist(-2.5f, 2.5f);
    for(int i = 1; i < 5; i++) {
        float height = dist(rng);
        models.emplace_back(new BronzeCoin());
        models.back()->set_position(glm::vec3(5.0 + i * 15.0, height, 0.0));
        models.emplace_back(new BronzeCoin());
        models.back()->set_position(glm::vec3(5.2 + i * 15.0, height, 0.0));
        models.emplace_back(new BronzeCoin());
        models.back()->set_position(glm::vec3(5.4 + i * 15.0, height, 0.0));
        models.emplace_back(new BronzeCoin());
        models.back()->set_position(glm::vec3(5.6 + i * 15.0, height, 0.0));
        models.emplace_back(new BronzeCoin());
        models.back()->set_position(glm::vec3(5.8 + i * 15.0, height, 0.0));

        height = dist(rng);
        models.emplace_back(new SilverCoin());
        models.back()->set_position(glm::vec3(7.0 + i * 15.0, height, 0.0));
        models.emplace_back(new SilverCoin());
        models.back()->set_position(glm::vec3(7.2 + i * 15.0, height, 0.0));
        models.emplace_back(new SilverCoin());
        models.back()->set_position(glm::vec3(7.4 + i * 15.0, height, 0.0));

        models.emplace_back(new GoldenCoin());
        models.back()->set_position(glm::vec3(9.0 + i * 15.0, 0.0, 0.0));
        models.emplace_back(new GoldenCoin());
        models.back()->set_position(glm::vec3(9.0 + i * 15.0, 0.2, 0.0));
        models.emplace_back(new GoldenCoin());
        models.back()->set_position(glm::vec3(9.0 + i * 15.0, -0.2, 0.0));

        models.emplace_back(new Fireline());
        models.back()->set_position(glm::vec3(2.0 + i * 15.0, 0.0, 0.0));
        models.back()->set_rotation(glm::vec3(0.0f, 0.0f, 30.0f));

        models.emplace_back(new Firebeam());
        models.back()->set_position(glm::vec3(12.0 + i * 15.0, 0.0, 0.0));
    }

    /* create display */
    for(int i = 5; i >= 0; i--) {
        auto d = new Digit();
        d->set_position(glm::vec3(-3.0f + 0.25f * i, 3.6f, 0.0f));
        models.emplace_back(d);
        fixed_models.push_back(models.back());
        score_digits.push_back(std::dynamic_pointer_cast<Digit, IModel>(models.back()));
    }

    auto d = new Digit();
    d->set_position(glm::vec3(0.0f, 3.6f, 0.0f));
    models.emplace_back(d);
    fixed_models.push_back(models.back());
    level_digit = std::dynamic_pointer_cast<Digit, IModel>(models.back());
    level_digit->set_digit(1);

    d = new Digit();
    d->set_position(glm::vec3(2.0f, 3.6f, 0.0f));
    models.emplace_back(d);
    fixed_models.push_back(models.back());
    lives_digit = std::dynamic_pointer_cast<Digit, IModel>(models.back());

    player = std::make_unique<Player>();

    magnet = std::make_shared<Magnet>();
    magnet->disable();
    magnet->set_position(glm::vec3(-3.5f, -2.0f, 0.0f));
    models.push_back(std::dynamic_pointer_cast<IModel, Magnet>(magnet));
    fixed_models.push_back(models.back());
    
    boomerang = std::make_shared<Boomerang>();
    boomerang->disable();
    models.push_back(std::dynamic_pointer_cast<IModel, Boomerang>(boomerang));

    dragon = std::make_shared<Dragon>();
    dragon->disable();
    dragon->set_position(glm::vec3(2.5f, 1.0f, 0.0f));
    models.push_back(std::dynamic_pointer_cast<IModel, Dragon>(dragon));
    fixed_models.push_back(models.back());

    iceball = std::make_shared<Iceball>();
    iceball->disable();    
    models.push_back(std::dynamic_pointer_cast<IModel, Iceball>(iceball));

    shield = std::make_shared<Shield>();
    shield->disable();    
    models.push_back(std::dynamic_pointer_cast<IModel, Shield>(shield));

    waterball = std::make_shared<WaterBall>();
    waterball->disable();    
    models.push_back(std::dynamic_pointer_cast<IModel, WaterBall>(waterball));
}

void levelDraw(GLFWwindow* window, glm::mat4 VP) {
    level.tick++;

    level.position += level.velocity;
    level.velocity.x = std::min(max_velocity_x - 0.01, level.velocity.x + 0.000001);

    if(level.tick%2000 == 0) {
        magnet->status() ? magnet->disable() : magnet->enable();
    }

    if(level.tick%1000 == 0) {
        boomerang->status() ? boomerang->disable() : boomerang->enable();
        if(boomerang->status()) {
            boomerang->set_position(glm::vec3(level.position.x + 5.0, 2.0f, 0.0f));
        }
    }

    if(level.tick == 5000 || level.tick == 6000) {
        dragon->status() ? dragon->disable() : dragon->enable();
    }

    if(dragon->status()) {
        auto dpos = dragon->get_position();
        dpos.y += 0.01 * signum(player->get_position().y - dpos.y);
        dpos.y = std::max(dpos.y, -2.0f); 
        dragon->set_position(dpos);

        if(level.tick%200 == 0) {
            auto ballpos = dpos;
            ballpos.y += 0.5f;
            ballpos.x -= 0.5f;
            iceball->reset();
            iceball->enable();
            iceball->set_position(ballpos);
        }
    }

    if(player->get_score() > 500 && shield_given == false) {
        shield_given = true;
        shield->enable();
        shield_tick = level.tick;
        player->set_shield(true);
    }

    if(level.tick - shield_tick > 1000) {
        shield->disable();
        player->set_shield(false);
    }

    key_state_t keys;
    keys.space = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
    keys.W = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
    keys.A = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS;
    keys.S = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;    
    keys.D = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS;
    player->input(keys);

    if(!waterball->status() && glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        auto ballpos = player->get_position();
        ballpos.y += 0.5f;
        ballpos.x += 0.5f;
        waterball->reset();
        waterball->enable();
        waterball->set_position(ballpos);
    }

    if(magnet->status()) {
        if(level.tick%2)
            player->push(glm::vec3(-step_velocity_x, -step_velocity_y, 0.0f));
    }

    for(auto& m : fixed_models) {
        m->set_position(m->get_position() + level.velocity);
    }

    player->tick(models);
    auto player_pos = player->get_position();
    player_pos.x = glm::clamp(player_pos.x, level.position.x - 3.75f, level.position.x + 3.75f);
    player->set_position(player_pos);

    for(auto& m : models) {
        if(m->is_dynamic()) {
            std::dynamic_pointer_cast<IDynamic, IModel>(m)->tick();
        }
    }

    if(shield->status()) {
        auto pos = player->get_position();
        pos.x += 0.3f;
        shield->set_position(pos);
    }

    int score = player->get_score();
    for(int i = 0; i < 6; i++) {
        score_digits[i]->set_digit(score % 10);
        score /= 10;
    }

    lives_digit->set_digit(player->get_lives() % 10);
    
    for(auto& m : models)
        m->draw(VP);
    player->draw(VP);
}