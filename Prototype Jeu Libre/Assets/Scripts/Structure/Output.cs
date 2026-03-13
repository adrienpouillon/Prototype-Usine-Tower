using TMPro;
using UnityEngine;

public class Output : MonoBehaviour
{
    [SerializeField] private Machine m_pMachine = null;
    [SerializeField] private Input m_pNext = null;
    [SerializeField] private Material m_PreviewMaterial = null;


    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        m_pMachine = transform.parent.Find("Machine").GetComponent<Machine>();

        BuildCursor b1 = GameObject.Find("Build_Cursor").GetComponent<BuildCursor>();
        m_PreviewMaterial = b1.m_previewMaterial;
    }
    
    public void OnCollisionEnter(Collision collision)
    {
        Input input = collision.gameObject.GetComponent<Input>();
        Debug.Log(collision.gameObject.name);
        if (input != null)
            m_pNext = input;
    }

    //void OnCollisionExit(Collision collision)
    //{
    //    m_pNext = null;
    //}

    public bool TransferToNext(string type, int amount)
    {
        if(m_pNext == null) 
        {
            Debug.Log("Output: TransferToNext - No next input found");
            return false; 
        }

        if (m_pNext.TryInput(type, amount))
            m_pMachine.outputSlot.amount -= amount;
        else
        {
            Debug.Log($"Output: TransferToNext - Failed to transfer {amount} of {type} to next input ({transform.parent.name} => {m_pNext.transform.parent.name})");
            return false;
        }
            
        Debug.Log($"Output: Transferred {amount} of {type} to next input ({m_pNext.transform.name})");
        return true;
    }

    // Update is called once per frame
    void Update()
    {
        m_pMachine = transform.parent.Find("Machine").GetComponent<Machine>();

        // Test forcé au lancement : on regarde s'il y a un Input autour de nous (rayon de 0.5m)
        Collider[] hitColliders = Physics.OverlapSphere(transform.position, 0.5f);
        foreach (var hit in hitColliders)
        {
            Input input = hit.GetComponent<Input>();
            if (input != null && hit.gameObject != this.gameObject && input.transform.parent.gameObject != transform.parent.gameObject && input.transform.GetComponent<MeshRenderer>().material != m_PreviewMaterial)
            {
                m_pNext = input;
            }
        }

        if (m_pMachine != null && m_pMachine.outputSlot.amount > 0)
        {
            Debug.Log($"Output fail: {TransferToNext(m_pMachine.outputSlot.type, m_pMachine.outputSlot.amount)}");
        }
    }
}
