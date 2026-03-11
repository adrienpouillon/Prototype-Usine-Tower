using NUnit.Framework;
using System;
using Unity.Mathematics;
using Unity.VisualScripting;
using UnityEditor.Animations;
using UnityEngine;
using UnityEngine.InputSystem;

public class BuildCursor : MonoBehaviour
{
    // INPUT SYSTEM
    private Player_InputSystemAction _inputs;

    // CURSOR
    private GameObject m_cursor;
    private PlayerCursor m_cursorFunction;

    // PREVIEW BUILDINGS
    private GameObject m_preview;
    [SerializeField] private Material m_previewMaterial;
    private Material[] m_originalMaterials;
    private int buildingIndex = 0;


    /// BASIC FUNCTIONS
    void Awake() => _inputs = new Player_InputSystemAction();
    void OnEnable() => _inputs.Enable();
    void OnDisable() => _inputs.Disable();

    


    /// METHODS
    void Start()
    {
        m_cursor = transform.parent.gameObject;
        m_cursorFunction = m_cursor.GetComponent<PlayerCursor>();

        GetNextPreview();
    }

    void GetNextPreview()
    {
        Vector3 cursorPos = m_cursor.transform.position;
        cursorPos.y = 0.1f;

        Tuple<GameObject, float3> previewWithScale = MasterBuilder.Instance.GetRandomBuildingWithScale();
        m_preview = Instantiate(previewWithScale.Item1, cursorPos, Quaternion.identity);
        m_preview.transform.localScale = previewWithScale.Item2;
        
        MasterBuilder.Instance.DisableScripts(m_preview);

        m_originalMaterials = MasterBuilder.Instance.GetMaterials(m_preview);
        MasterBuilder.Instance.SetMaterial(m_preview, m_previewMaterial);

        m_preview.transform.parent = transform;
    }

    void GetPreview(int index)
    {
        Destroy(m_preview);

        Vector3 cursorPos = m_cursor.transform.position;
        cursorPos.y = 0.1f;

        Tuple<GameObject, float3> previewWithScale = MasterBuilder.Instance.GetBuilding(index);
        m_preview = Instantiate(previewWithScale.Item1, cursorPos, Quaternion.identity);
        m_preview.transform.localScale = previewWithScale.Item2;

        MasterBuilder.Instance.DisableScripts(m_preview);

        m_originalMaterials = MasterBuilder.Instance.GetMaterials(m_preview);
        MasterBuilder.Instance.SetMaterial(m_preview, m_previewMaterial);

        m_preview.transform.parent = transform;

        buildingIndex = index;
    }

    void SwitchBuilding()
    {
        if(_inputs.Build_Mode.Shortcut1.WasPressedThisFrame())
        {
            GetPreview(0);
        }
        else if(_inputs.Build_Mode.Shortcut2.WasPressedThisFrame())
        {
            GetPreview(1);
        }
        else if(_inputs.Build_Mode.Shortcut3.WasPressedThisFrame())
        {
            GetPreview(2);
        }
    }

    void Build()
    {
        Vector2 cursorPos = m_cursorFunction.GetGridSnappedPosition(m_cursor.transform.position);

        if (GridManager.Instance.IsFree(new Vector2(cursorPos.x, cursorPos.y)))
        {
            GameObject newBuild = m_preview;

            MasterBuilder.Instance.EnableScripts(newBuild);
            MasterBuilder.Instance.SetMaterial(newBuild, m_originalMaterials);

            GridManager.Instance.BookCoordinate(new Vector2(cursorPos.x, cursorPos.y), m_cursor, newBuild);

            newBuild.transform.parent = null;

            foreach(Transform child in newBuild.transform)
            {
                child.AddComponent<BoxCollider>();
            }

            m_preview = null;

            GetPreview(buildingIndex);
        }
    }

    void Update()
    {
        transform.position = m_cursor.transform.position;
        // BUILD
        if (_inputs.Build_Mode.Use.WasPressedThisFrame())
            Build();

        // ROTATE
        if(_inputs.Build_Mode.Rotate.WasPressedThisFrame())
            m_preview.transform.Rotate(0f, 90f, 0f);

        SwitchBuilding();
    }
}