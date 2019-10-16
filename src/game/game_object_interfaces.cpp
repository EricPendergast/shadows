#include "game_object_interfaces.h"

template <typename GameObjectSubclass>
void tryAdd(std::shared_ptr<GameObject>& g, std::vector<std::shared_ptr<GameObjectSubclass>>& v) {
    std::shared_ptr<GameObjectSubclass> g_casted = std::dynamic_pointer_cast<GameObjectSubclass>(g);
    if (g_casted != nullptr) {
        v.push_back(g_casted);
    }
}

void GameObjects::registerObj(std::shared_ptr<GameObject> gameObject) {
    tryAdd(gameObject, physicalObjs);
    tryAdd(gameObject, renderableObjs);
    tryAdd(gameObject, pixelCollidableObjs);
    tryAdd(gameObject, opaqueObjs);
    tryAdd(gameObject, shadowCastableObjs);
    tryAdd(gameObject, userControllableObjs);
    tryAdd(gameObject, interactableObjs);
    tryAdd(gameObject, interactorObjs);
}
