using Unity.VisualScripting;
using UnityEngine;

public class Button : MonoBehaviour
{
    [SerializeField] private BuildCursor m_pTarget = null;
    [SerializeField] private BuildCursor.BuildMode m_BuildMode = BuildCursor.BuildMode.COUNT;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    public void OnButtonClick()
    {
        if (m_pTarget != null)
            m_pTarget.SwitchBuildMode(m_BuildMode);
    }

    // Update is called once per frame
    void Update()
    {
    }
}
