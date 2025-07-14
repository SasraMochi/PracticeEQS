#include "ActorManager.h"
#include "Actor.h"

#include <algorithm>
#include <iterator>

//�f�X�g���N�^
ActorManager::~ActorManager(){
    clear();
}

//�A�N�^�[�̒ǉ�
void ActorManager::add(Actor* actor){
    mpActors.push_back(actor);
}

//�A�N�^�[�̍X�V
void ActorManager::update(float delta_time){
    for (auto actor : mpActors) {
        actor->update(delta_time);
    }
}

//�A�N�^�[�̒x���X�V
void ActorManager::late_update(float delta_time){
    for (auto actor : mpActors) {
        actor->late_update(delta_time);
    }
}

//�A�N�^�[�̕`��
void ActorManager::draw() const{
    for (auto actor : mpActors) {
        actor->draw();
    }
}

//�������A�N�^�[�̕`��
void ActorManager::draw_transparent() const{
    for (auto actor : mpActors) {
        actor->draw_transparent();
    }
}

//�A�N�^�[��GUI�`��
void ActorManager::draw_gui() const{
    for (auto actor : mpActors) {
        actor->draw_gui();
    }
}

//�A�N�^�[�̏Փ˔���
void ActorManager::collide(){
    for (auto i = mpActors.begin(); i != mpActors.end(); ++i) {
        for (auto j = std::next(i); j != mpActors.end(); ++j) {
            (*i)->collide(**j);
        }
    }
}

//���S���Ă���A�N�^�[�̍폜
void ActorManager::remove(){
    for (auto i = mpActors.begin(); i != mpActors.end();) {
        if ((*i)->is_dead()) {
            delete* i;
            i = mpActors.erase(i);
        }else {
            ++i;
        }
    }
}

//�A�N�^�[�̌���
Actor* ActorManager::find(const std::string& name) const{
    auto result = std::find_if(
        mpActors.begin(), mpActors.end(), 
        [&](Actor* actor) { return actor->name() == name; }
    );

    if (result == mpActors.end()) return nullptr;

    return *result;
}

//�w�肵���^�O�������A�N�^�[�̌���
std::vector<Actor*> ActorManager::find_with_tag(const std::string& tag) const{
    std::vector<Actor*> result;

    std::copy_if(mpActors.begin(), mpActors.end(), std::back_inserter(result),
        [&](Actor* actor) { return actor->tag() == tag; });

    return result;
}

//�A�N�^�[����Ԃ�
int ActorManager::count() const{
    return (int)mpActors.size();
}

//�w�肵���^�O�̃A�N�^�[����Ԃ�
int ActorManager::count_with_tag(const std::string& tag) const{
    auto result = std::count_if(
        mpActors.begin(), mpActors.end(), 
        [&](Actor* actor) { return actor->tag() == tag; }
    );

    return static_cast<int>(result);
}

//���b�Z�[�W�̑��M
void ActorManager::send_message(const std::string& message, void* param){
    for (auto actor : mpActors) {
        actor->handle_message(message, param);
    }
}

//����
void ActorManager::clear(){
    for (auto actor : mpActors) {
        delete actor;
    }
    mpActors.clear();
}