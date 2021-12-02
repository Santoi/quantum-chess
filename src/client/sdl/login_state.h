#ifndef QUANTUM_CHESS_PROJ_LOGIN_STATE_H
#define QUANTUM_CHESS_PROJ_LOGIN_STATE_H

#include "login_renderer.h"
#include "texture_sprite.h"
#include "login.h"
#include "button.h"
#include "text_entry_button.h"
#include <atomic>
#include <vector>
#include <memory>

class LoginRenderer;

class LoginState {
protected:
    Login& login;
    std::vector<std::unique_ptr<Button>> buttons_ptr;
    std::vector<std::unique_ptr<TextEntryButton>> text_entry_buttons_ptr;

public:

    LoginState() = delete;

    explicit LoginState(Login& login_);

    virtual bool clientIsConnectedToMatch() = 0;

    virtual void tellRendererWhatToRender(LoginRenderer& login_renderer) = 0;

    virtual void fillWithActiveButtons(std::list<std::reference_wrapper<Button>>& active_buttons) = 0;

    virtual void fillWithActiveTextEntryButtons(std::list<std::reference_wrapper<TextEntryButton>>&
                                                active_text_entries) = 0;

    virtual int proccessTokens(std::list<std::string>&& tokens) = 0;

    void resetPressedButtons();

    ~LoginState() = default;
};

class NotConnectedToServerState: public LoginState {
public:

    NotConnectedToServerState(Login& login_, Renderer& renderer_);

    bool clientIsConnectedToMatch() override;

    void tellRendererWhatToRender(LoginRenderer& login_renderer) override;

    void fillWithActiveButtons(std::list<std::reference_wrapper<Button>>& active_buttons) override;

    void fillWithActiveTextEntryButtons(std::list<std::reference_wrapper<TextEntryButton>>&
                                        active_text_entries) override;

    int proccessTokens(std::list<std::string>&& tokens) override;

    ~NotConnectedToServerState() = default;
};

class NotConnectedToMatchState: public LoginState {
public:

    NotConnectedToMatchState(Login& login_, Renderer& renderer_);

    bool clientIsConnectedToMatch() override;

    void tellRendererWhatToRender(LoginRenderer& login_renderer) override;

    void fillWithActiveButtons(std::list<std::reference_wrapper<Button>>& active_buttons) override;

    void fillWithActiveTextEntryButtons(std::list<std::reference_wrapper<TextEntryButton>>&
    active_text_entries) override;

    int proccessTokens(std::list<std::string>&& tokens) override;

    ~NotConnectedToMatchState() = default;
};

class ConnectedToMatchState: public LoginState {
private:
    TextureSprite texture_sprite;

public:
    ConnectedToMatchState(Login& login_, Renderer& renderer_);

    bool clientIsConnectedToMatch() override;

    void tellRendererWhatToRender(LoginRenderer& login_renderer) override;

    void fillWithActiveButtons(std::list<std::reference_wrapper<Button>>& active_buttons) override;

    void fillWithActiveTextEntryButtons(std::list<std::reference_wrapper<TextEntryButton>>&
    active_text_entries) override;

    int proccessTokens(std::list<std::string>&& tokens) override;

    ~ConnectedToMatchState() = default;
};


#endif //QUANTUM_CHESS_PROJ_LOGIN_STATE_H
