using UnityEngine;

public class DestroyCursor : MonoBehaviour
{
    // INPUT SYSTEM
    private Player_InputSystemAction _inputs;

    // CURSOR
    private GameObject m_cursor;
    private PlayerCursor m_cursorFunction;


    /// BASIC FUNCTIONS
    void Awake() => _inputs = new Player_InputSystemAction();
    void OnEnable() => _inputs.Enable();
    void OnDisable() => _inputs.Disable();



    /// METHODS
    void Start()
    {
        m_cursor = transform.parent.gameObject;
        m_cursorFunction = m_cursor.GetComponent<PlayerCursor>();
    }

    void Destroy()
    {
        GameObject target = m_cursorFunction.GetCursorGameObject();
        if (target != null)
        {
            Vector2 cursorPos = m_cursorFunction.GetGridSnappedPosition(m_cursor.transform.position);

            if (GridManager.Instance.GetOrderer(cursorPos) != m_cursor)
                return;

            GridManager.Instance.ReleaseCoordinate(cursorPos);
            Destroy(target);
        }
    }

    void Update()
    {
        transform.position = m_cursor.transform.position;
        /// BUILD
        if (_inputs.Build_Mode.Use.WasPressedThisFrame())
            Destroy();
    }
}
