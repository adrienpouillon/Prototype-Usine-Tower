using UnityEngine;

public class Input : MonoBehaviour
{
    [SerializeField] private Machine m_pMachine = null;
    [SerializeField] private bool m_IsConveyor = false;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void GetMachine()
    {
        m_pMachine = transform.parent.Find("Machine").GetComponent<Machine>();
    }

    public bool TryInput(string type, int amount)
    {
        if (m_pMachine == null) GetMachine();
        if(m_pMachine == null)
        {
            Debug.LogError("Input: TryInput - No machine found for this input");
            return false;
        }

        if(m_IsConveyor == false)
        {
            if (m_pMachine.TryAddResource(type, amount))
            {
                Debug.Log($"Input: Added {amount} of {type} to machine");
                return true;
            }
            else
            {
                Debug.Log($"Input: Failed to add {amount} of {type} to machine");
                return false;
            }
        }
        else
        {
            m_pMachine.outputSlot.type = type;
            m_pMachine.outputSlot.amount = amount;
            return true;
        }
    }
}
