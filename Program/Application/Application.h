#pragma once

namespace rsk::application
{
    /// <summary>
    /// �A�v���P�[�V�������Ǘ�����N���X
    /// </summary>
    class Application
    {
    public:
        Application()           = default;
        virtual ~Application()  = default;
        [[nodiscard]] bool Run();
    private:
        [[nodiscard]] virtual bool Initialize() = 0;
        [[nodiscard]] virtual bool Update()     = 0;
        virtual void Draw()                     = 0;
        virtual void Finalize()                 = 0;
    };
}
