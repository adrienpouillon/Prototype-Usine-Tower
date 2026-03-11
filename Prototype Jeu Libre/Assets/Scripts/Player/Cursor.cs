using UnityEngine;
using UnityEngine.InputSystem;

public class PlayerCursor : MonoBehaviour
{
    // GRID DETECTION
    [SerializeField] private LayerMask m_groundLayer;
    [SerializeField] public float m_gridSize = 5f;

    // CAMERA
    private Camera m_mainCamera;

    // INPUT SYSTEM
    private Player_InputSystemAction _inputs;

    // STATE
    private enum CursorState
    {
        Build,
        Destroy,
        Count
    }
    [SerializeField] private CursorState m_stateMachine;

    [SerializeField] private GameObject m_BuildCursor;
    [SerializeField] private GameObject m_DestroyCursor;


    /// BASIC FUNCTIONS
    void Awake() => _inputs = new Player_InputSystemAction();
    void OnEnable() => _inputs.Enable();
    void OnDisable() => _inputs.Disable();

    /// TOOLS
    public GameObject GetCursorGameObject()
    {
        Vector2 cursorPos = new Vector2(gameObject.transform.position.x, gameObject.transform.position.z);
        return GridManager.Instance.GetOccupant(GetGridSnappedPosition(gameObject.transform.position));
    }

    public Vector2 GetGridSnappedPosition(Vector3 position)
    {
        // grid snapping
        float x = Mathf.Round(position.x / m_gridSize) * m_gridSize;
        float z = Mathf.Round(position.z / m_gridSize) * m_gridSize;

        //return new Vector2(x + (m_gridSize * 0.5f), z + (m_gridSize * 0.5f));
        return new Vector2(x, z);
    }

    public GameObject GetCursorState()
    {
        switch(m_stateMachine)
        {
            case CursorState.Build:
                return m_BuildCursor;
            case CursorState.Destroy:
                return m_DestroyCursor;
            default:
                return null;
        }
    }

    /// METHODS
    void Start()
    {
        m_mainCamera = Camera.main;
    }

    void UpdateCursorPosition()
    {
        Vector2 mousePos = Mouse.current.position.ReadValue();
        Ray ray = m_mainCamera.ScreenPointToRay(mousePos);
        RaycastHit hit;

        if (Physics.Raycast(ray, out hit, Mathf.Infinity, m_groundLayer))
        {
            // grid snapping
            float x = Mathf.Round(hit.point.x / m_gridSize) * m_gridSize;
            float z = Mathf.Round(hit.point.z / m_gridSize) * m_gridSize;

            Vector3 position = new Vector3(x, hit.point.y + 2.5f, z);
            transform.position = position;
        }
    }

    void SwitchMode()
    {
        if(m_stateMachine == CursorState.Count - 1)
            m_stateMachine = 0;
        else
            m_stateMachine++;

        switch(m_stateMachine)
        {
            case CursorState.Build:
                m_BuildCursor.SetActive(true);
                m_DestroyCursor.SetActive(false);
                break;
            case CursorState.Destroy:
                m_BuildCursor.SetActive(false);
                m_DestroyCursor.SetActive(true);
                break;
        }
    }

    void Update()
    {
        UpdateCursorPosition();

        if(_inputs.Build_Mode.Switch_Mode.WasPressedThisFrame())
            SwitchMode();
    }
}
