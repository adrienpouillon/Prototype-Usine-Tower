using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.InputSystem;

public class Camera_Build: MonoBehaviour
{
    private Player_InputSystemAction _inputs;

    //CAMERA MOVEMENT SPEED
    [SerializeField] private float m_horizontalSpeed = 15f;
    [SerializeField] private float m_horizontalSprintSpeed = 60f;

    [SerializeField] private float m_verticalSpeed = 150f;


    // BASIC FUNCTIONS
    void Awake() => _inputs = new Player_InputSystemAction();
    void OnEnable() => _inputs.Enable();
    void OnDisable() => _inputs.Disable();


    

    /// METHODS
    Vector3 MoveCameraHorizontal()
    {
        Vector2 inputVector = _inputs.Player.Move.ReadValue<Vector2>();

        if(_inputs.Player.Sprint.IsPressed())
            return new Vector3(-inputVector.y * m_horizontalSprintSpeed, 0, inputVector.x * m_horizontalSprintSpeed);
        else
            return new Vector3(-inputVector.y * m_horizontalSpeed, 0, inputVector.x * m_horizontalSpeed);
    }

    Vector3 MoveCameraVertical()
    {
        Vector2 mouseWheel = _inputs.Player.Zoom.ReadValue<Vector2>();

        return new Vector3(0, -mouseWheel.y * m_verticalSpeed, 0);
    }

    

    void Update()
    {
        /// CAMERA MOVEMENT
        Vector3 move = new Vector3(0f, 0f, 0f);

        if(_inputs.Player.Move.IsPressed())
            move = MoveCameraHorizontal();
        if(_inputs.Player.Zoom.IsPressed())
            move.y = MoveCameraVertical().y;

        transform.Translate(move * Time.deltaTime, Space.World);
    }
}